#include "fanbee.h"

#include <stdint.h>
#include <string.h>
#include <ti/display/Display.h>
#include <ti/drivers/NVS.h>
#include <ti/drivers/apps/Button.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/family/arm/cc26xx/Timer.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Task.h>

#include "bdb_interface.h"
#include "cui.h"
#include "gp_common.h"
#include "nvintf.h"
#include "ota_client.h"
#include "ti_drivers_config.h"
#include "util_timer.h"
#include "zcl_config.h"
#include "zcl_ota.h"
#include "zcl_port.h"
#include "zcomdef.h"
#include "zstackapi.h"
#include "zstackmsg.h"

uint8 fanbee_Basic_ManufacturerName[] = {11, 'L', 'o', 'r', 'e', 'n', 'z', ' ', 'B', 'r', 'u', 'n'};
uint8 fanbee_Basic_ModelIdentifier[] = {7, 'F', 'a', 'n', 'B', 'e', 'e', '1'};
const enum8 DEFAULT_FANBEE_BASIC_POWER_SOURCE = POWER_SOURCE_DC;
const uint8 DEFAULT_FANBEE_LEVEL_CURRENT_LEVEL = 254;

// Semaphore used to post events to the application thread
static Semaphore_Handle appSemHandle;
static Semaphore_Struct appSem;

// App service ID used for messaging with stack service task
uint8_t sampleApp_serviceTaskId;

// App service task events, set by the stack service task when sending a message
static uint32_t appServiceTaskEvents;

// Passed in function pointers to the NV driver
static NVINTF_nvFuncts_t *nvm = NULL;

// Constants (TODO: Determine)
static const uint32_t valve_open = 2300;
static const uint32_t valve_closed = 600;

// Peripheral handles
static Display_Handle debug_display_handle;

static Button_Handle pair_btn_handle;

static LED_Handle act_led_handle;

static Clock_Handle tacho_clk_handle;
static Clock_Struct tacho_clk_struct;

static PWM_Handle pwm_fan = NULL;

static PWM_Handle pwm_srv1 = NULL, pwm_srv2 = NULL;

static bool joined = false;

// Functions for sample application setup
void sampleApp_task(NVINTF_nvFuncts_t *pfnNV);
static void fanbee_process_loop();
static void fanbee_initPeripherals();
static void fanbee_processZStackMsgs(zstackmsg_genericReq_t *pMsg);
static void fanbee_processAfIncomingMsgInd(zstack_afIncomingMsgInd_t *pInMsg);
static void fanbee_initZCLGeneral();
static void fanbee_ProcessCommissioningStatus(bdbCommissioningModeMsg_t *bdbCommissioningModeMsg);

// Update hooks
static void fanbee_updateOutputs();
static void fanbee_updateLevel();
static void fanbee_updateOnOff();

// Functions to process ZCL Foundation incoming Command/Response messages
static uint8_t fanbee_ProcessIncomingMsg(zclIncoming_t *pInMsg);

void Board_initHook(void) { PWM_init(); }

static NVINTF_itemID_t nvOnOffId = {
    .systemID = NVINTF_SYSID_APP,
    .itemID = FANBEE_NV_ONOFF,
    .subID = 0,
};
static NVINTF_itemID_t nvCurrentLevelId = {
    .systemID = NVINTF_SYSID_APP,
    .itemID = FANBEE_NV_CURRENT_LEVEL,
    .subID = 0,
};

// Application task entry point
void sampleApp_task(NVINTF_nvFuncts_t *pfnNV) {
  // Save and register the function pointers to the NV drivers
  nvm = pfnNV;
  if (nvm == NULL) {
    Display_printf(debug_display_handle, 0, 0, "No NVM available");
  }
  zclport_registerNV(nvm, ZCL_PORT_SCENE_TABLE_NV_ID);

  // Create semaphores for messages / events
  Semaphore_Params semParam;
  Semaphore_Params_init(&semParam);
  semParam.mode = ti_sysbios_knl_Semaphore_Mode_COUNTING;
  appSemHandle = Semaphore_construct(&appSem, 0, &semParam);
  sampleApp_serviceTaskId = OsalPort_registerTask(Task_self(), appSemHandle, &appServiceTaskEvents);

  fanbee_initPeripherals();

  // Initialize Zigbee
  fanbee_initZCLGeneral();
  gp_endpointInit(sampleApp_serviceTaskId);
  app_Green_Power_Init(sampleApp_serviceTaskId, &appServiceTaskEvents, appSemHandle,
                       FANBEE_GP_DATA_SEND_EVT, FANBEE_GP_EXPIRE_DUPLICATE_EVT,
                       FANBEE_GP_TEMP_MASTER_EVT);

  uint32_t onOffErr = NVINTF_NOTFOUND;
  uint32_t levelErr = NVINTF_NOTFOUND;
  if (nvm->readItem) {
    nvm->readItem(nvCurrentLevelId, 0, sizeof(fanbee_Level_CurrentLevel),
                  &fanbee_Level_CurrentLevel);
    nvm->readItem(nvOnOffId, 0, sizeof(fanbee_OnOff_OnOff), &fanbee_OnOff_OnOff);
  }

  if ((onOffErr == NVINTF_NOTFOUND) && nvm->createItem) {
    nvm->createItem(nvOnOffId, sizeof(fanbee_OnOff_OnOff), &fanbee_OnOff_OnOff);
  }
  if ((levelErr == NVINTF_NOTFOUND) && nvm->createItem) {
    nvm->createItem(nvCurrentLevelId, sizeof(fanbee_Level_CurrentLevel),
                    &fanbee_Level_CurrentLevel);
  }

  // Set up output state
  fanbee_updateOutputs();

  // Enable line driver IC outputs.
  GPIO_write(CONFIG_DRV_EN, 1);

  Display_printf(debug_display_handle, 0, 0, "Init done, starting loop");

  // No return from task process
  fanbee_process_loop();
}

static uint32_t fan_tacho_pulses = 0;
void fanbee_tachoCB(uint_least8_t index) { fan_tacho_pulses++; }

static void fanbee_tachoSumHandler() {
  appServiceTaskEvents |= FANBEE_TACHO_EVT;
  Semaphore_post(appSemHandle);
}

static void fanbee_pairButtonHandler(Button_Handle handle, Button_EventMask events) {
  if ((events & Button_EV_CLICKED) == Button_EV_CLICKED) {
    appServiceTaskEvents |= FANBEE_PAIR_EVT;
    Semaphore_post(appSemHandle);
  }
  if ((events & Button_EV_LONGCLICKED) == Button_EV_LONGCLICKED) {
    appServiceTaskEvents |= FANBEE_RESET_EVT;
    Semaphore_post(appSemHandle);
  }
}

static void fanbee_initPeripherals() {
  debug_display_handle = Display_open(Display_Type_ANY, NULL);

  Clock_Params clock_params;
  Clock_Params_init(&clock_params);
  clock_params.period = 3000000;  // Every 30s
  tacho_clk_handle =
      Clock_construct(&tacho_clk_struct, fanbee_tachoSumHandler, 1000000, &clock_params);

  Button_init();
  Button_Params button_params;
  Button_Params_init(&button_params);
  button_params.buttonCallback = fanbee_pairButtonHandler;

  pair_btn_handle = Button_open(CONFIG_BTN_PAIR, &button_params);

  LED_init();
  LED_Params led_params;
  LED_Params_init(&led_params);
  act_led_handle = LED_open(CONFIG_LED_GREEN, &led_params);

  // Taken from Noctua PWM specification white paper at
  // https://noctua.at/pub/media/wysiwyg/Noctua_PWM_specifications_white_paper.pdf
  PWM_Params fan_pwm_params;
  PWM_Params_init(&fan_pwm_params);
  fan_pwm_params.periodUnits = PWM_PERIOD_HZ;
  fan_pwm_params.periodValue = 25000;
  fan_pwm_params.dutyUnits = PWM_DUTY_FRACTION;
  pwm_fan = PWM_open(CONFIG_PWM_FAN1, &fan_pwm_params);
  if (pwm_fan == NULL) {
    Display_printf(debug_display_handle, 0, 0, "Failed to open FAN PWM");
  }

  // Servos expect one pulse every 20ms, 1500us pulse with is neutral,
  // +/- 500us moves 90° in either direction.
  PWM_Params servo_pwm_params;
  PWM_Params_init(&servo_pwm_params);
  servo_pwm_params.periodUnits = PWM_PERIOD_US;
  servo_pwm_params.periodValue = 20000;  // 20ms
  servo_pwm_params.dutyUnits = PWM_DUTY_US;
  servo_pwm_params.dutyValue = 1500;  // Neutral
  pwm_srv1 = PWM_open(CONFIG_PWM_SRV1, &servo_pwm_params);
  pwm_srv2 = PWM_open(CONFIG_PWM_SRV2, &servo_pwm_params);

  // Enable PWM outputs (output still gated by disabled driver IC)
  PWM_start(pwm_fan);
  PWM_start(pwm_srv1);
  PWM_start(pwm_srv2);

  // Enable tacho-related stuff
  GPIO_enableInt(CONFIG_FAN1_TACHO_CONST);
  Clock_start(tacho_clk_handle);

  // Start slow-blinking until network joined
  LED_startBlinking(act_led_handle, 2000, LED_BLINK_FOREVER);
}

// Event Loop Processor
static void fanbee_process_loop(void) {
  for (;;) {
    zstackmsg_genericReq_t *pMsg = NULL;
    // Wait for response message
    if (Semaphore_pend(appSemHandle, BIOS_WAIT_FOREVER)) {
      // Retrieve the response message
      if ((pMsg = (zstackmsg_genericReq_t *)OsalPort_msgReceive(sampleApp_serviceTaskId)) != NULL) {
        // Process the message from the stack
        fanbee_processZStackMsgs(pMsg);

        // Free any separately allocated memory
        Zstackapi_freeIndMsg(pMsg);
      }

      if (pMsg != NULL) {
        OsalPort_msgDeallocate((uint8_t *)pMsg);
      }
      if (appServiceTaskEvents & FANBEE_TACHO_EVT) {
        // (pulses / 2) * (60s/30s) = 1
        int32_t rpm = fan_tacho_pulses;
        fan_tacho_pulses = 0;
        Display_printf(debug_display_handle, 0, 0, "Fan RPM: %d", rpm);
        appServiceTaskEvents &= ~FANBEE_TACHO_EVT;
      }
      if (appServiceTaskEvents & FANBEE_RESET_EVT) {
        Display_printf(debug_display_handle, 0, 0, "Resetting ZStack");
        joined = false;
        LED_startBlinking(act_led_handle, 2000, LED_BLINK_FOREVER);
        // TODO: Clear NVM
        Zstackapi_bdbResetLocalActionReq(sampleApp_serviceTaskId);
        appServiceTaskEvents &= ~FANBEE_RESET_EVT;
      }
      if (appServiceTaskEvents & FANBEE_PAIR_EVT) {
        if (!joined) {
          zstack_bdbStartCommissioningReq_t zstack_bdbStartCommissioningReq;
          zstack_bdbStartCommissioningReq.commissioning_mode = BDB_COMMISSIONING_MODE_NWK_STEERING;
          Zstackapi_bdbStartCommissioningReq(sampleApp_serviceTaskId,
                                             &zstack_bdbStartCommissioningReq);
          LED_startBlinking(act_led_handle, 500, LED_BLINK_FOREVER);
        } else {
          LED_startBlinking(act_led_handle, 250, 2);
        }
        appServiceTaskEvents &= ~FANBEE_PAIR_EVT;
      }
      // ZigBee Green Power Proxy
      if (appServiceTaskEvents & FANBEE_GP_DATA_SEND_EVT) {
        if (zgGP_ProxyCommissioningMode == TRUE)
          zcl_gpSendCommissioningNotification();
        else
          zcl_gpSendNotification();
        appServiceTaskEvents &= ~FANBEE_GP_DATA_SEND_EVT;
      }
      if (appServiceTaskEvents & FANBEE_GP_EXPIRE_DUPLICATE_EVT) {
        gp_expireDuplicateFiltering();
        appServiceTaskEvents &= ~FANBEE_GP_EXPIRE_DUPLICATE_EVT;
      }
      if (appServiceTaskEvents & FANBEE_GP_TEMP_MASTER_EVT) {
        gp_returnOperationalChannel();
        appServiceTaskEvents &= ~FANBEE_GP_TEMP_MASTER_EVT;
      }

#if defined(OTA_CLIENT_INTEGRATED)
      otaClient_event_loop();
#endif
    }
  }
}

// Process event from Stack (pMsg is incoming message)
static void fanbee_processZStackMsgs(zstackmsg_genericReq_t *pMsg) {
  switch (pMsg->hdr.event) {
    case zstackmsg_CmdIDs_BDB_NOTIFICATION:
      fanbee_ProcessCommissioningStatus(&(((zstackmsg_bdbNotificationInd_t *)pMsg)->Req));
      break;
    case zstackmsg_CmdIDs_AF_INCOMING_MSG_IND:
      fanbee_processAfIncomingMsgInd(&(((zstackmsg_afIncomingMsgInd_t *)pMsg)->req));
      break;
    case zstackmsg_CmdIDs_BDB_CBKE_TC_LINK_KEY_EXCHANGE_IND: {
      zstack_bdbCBKETCLinkKeyExchangeAttemptReq_t zstack_bdbCBKETCLinkKeyExchangeAttemptReq = {
          /* Z3.0 has not defined CBKE yet, so lets attempt default TC Link Key exchange procedure
           * by reporting CBKE failure. */
          .didSuccess = false,
      };

      Zstackapi_bdbCBKETCLinkKeyExchangeAttemptReq(sampleApp_serviceTaskId,
                                                   &zstack_bdbCBKETCLinkKeyExchangeAttemptReq);
    } break;

    case zstackmsg_CmdIDs_BDB_FILTER_NWK_DESCRIPTOR_IND:

      /*   User logic to remove networks that do not want to join
       *   Networks to be removed can be released with Zstackapi_bdbNwkDescFreeReq */

      Zstackapi_bdbFilterNwkDescComplete(sampleApp_serviceTaskId);
      break;

    case zstackmsg_CmdIDs_BDB_IDENTIFY_TIME_CB: {
      if (fanbee_Identify_IdentifyTime > 0)
        LED_startBlinking(act_led_handle, 500, LED_BLINK_FOREVER);
      else
        LED_stopBlinking(act_led_handle);
    } break;

    case zstackmsg_CmdIDs_AF_DATA_CONFIRM_IND:
      // Ignore, nothing to do
      break;

    // ZigBee Green Power Proxy
    case zstackmsg_CmdIDs_GP_DATA_IND:
      gp_processDataIndMsg(&(((zstackmsg_gpDataInd_t *)pMsg)->Req));
      break;
    case zstackmsg_CmdIDs_GP_SECURITY_REQ:
      gp_processSecRecMsg(&(((zstackmsg_gpSecReq_t *)pMsg)->Req));
      break;
    case zstackmsg_CmdIDs_GP_CHECK_ANNCE:
      gp_processCheckAnnceMsg(&(((zstackmsg_gpCheckAnnounce_t *)pMsg)->Req));
      break;
    case zstackmsg_CmdIDs_GP_COMMISSIONING_MODE_IND:
      // gp_SetProxyCommissioningMode(((zstackmsg_gpCommissioningModeInd_t *)pMsg)->Req.isEntering);
      break;

    default:
      Display_printf(debug_display_handle, 0, 0, "Got unknown ZStack Msg Event 0x%x",
                     pMsg->hdr.event);
      break;
  }
}

// Process AF Incoming Message Indication message
static void fanbee_processAfIncomingMsgInd(zstack_afIncomingMsgInd_t *pInMsg) {
  afIncomingMSGPacket_t afMsg;
  // Convert to ZCL
  afMsg.groupId = pInMsg->groupID;
  afMsg.clusterId = pInMsg->clusterId;
  afMsg.srcAddr.endPoint = pInMsg->srcAddr.endpoint;
  afMsg.srcAddr.panId = pInMsg->srcAddr.panID;
  afMsg.srcAddr.addrMode = (afAddrMode_t)pInMsg->srcAddr.addrMode;
  if ((afMsg.srcAddr.addrMode == afAddr16Bit) || (afMsg.srcAddr.addrMode == afAddrGroup) ||
      (afMsg.srcAddr.addrMode == afAddrBroadcast)) {
    afMsg.srcAddr.addr.shortAddr = pInMsg->srcAddr.addr.shortAddr;
  } else if (afMsg.srcAddr.addrMode == afAddr64Bit) {
    OsalPort_memcpy(afMsg.srcAddr.addr.extAddr, &(pInMsg->srcAddr.addr.extAddr), Z_EXTADDR_LEN);
  }
  afMsg.macDestAddr = pInMsg->macDestAddr;
  afMsg.endPoint = pInMsg->endpoint;
  afMsg.wasBroadcast = pInMsg->wasBroadcast;
  afMsg.LinkQuality = pInMsg->linkQuality;
  afMsg.correlation = pInMsg->correlation;
  afMsg.rssi = pInMsg->rssi;
  afMsg.SecurityUse = pInMsg->securityUse;
  afMsg.timestamp = pInMsg->timestamp;
  afMsg.nwkSeqNum = pInMsg->nwkSeqNum;
  afMsg.macSrcAddr = pInMsg->macSrcAddr;
  afMsg.radius = pInMsg->radius;
  afMsg.cmd.DataLength = pInMsg->n_payload;
  afMsg.cmd.Data = pInMsg->pPayload;

  zcl_ProcessMessageMSG(&afMsg);
}

void fanbee_OnOffCB(uint8_t cmd) {
  afIncomingMSGPacket_t *pPtr = zcl_getRawAFMsg();
  switch (cmd) {
    case COMMAND_ON_OFF_ON:
      fanbee_OnOff_OnOff = 1;
      break;
    case COMMAND_ON_OFF_OFF:
      fanbee_OnOff_OnOff = 0;
      break;
    case COMMAND_ON_OFF_TOGGLE:
      fanbee_OnOff_OnOff = !fanbee_OnOff_OnOff;
      break;
  }
  fanbee_updateOutputs();
  fanbee_updateOnOff();
}

void fanbee_LevelControlMoveToLevelCB(zclLCMoveToLevel_t *pCmd) {
  fanbee_Level_CurrentLevel = pCmd->level;
  if (pCmd->withOnOff) {
    if (pCmd->level == 0) {
      fanbee_OnOff_OnOff = 0;
    }
    if (pCmd->level > 0) {
      fanbee_OnOff_OnOff = 1;
    }
    fanbee_updateOnOff();
  }
  fanbee_updateOutputs();
  fanbee_updateLevel();
}

static const uint32_t min_duty = PWM_DUTY_FRACTION_MAX / 4;  // 25% for Noctua fans
static const uint32_t duty_scale = (PWM_DUTY_FRACTION_MAX - min_duty) / 254;

static void fanbee_updateOutputs() {
  uint32_t fan_speed = fanbee_OnOff_OnOff ? fanbee_Level_CurrentLevel : 0;
  GPIO_write(CONFIG_FAN1_EN, fan_speed > 0);
  uint32_t pwm_duty = 0;
  if (fan_speed > 0) {
    pwm_duty = min_duty + (duty_scale * fan_speed);
  }
  PWM_setDuty(pwm_fan, pwm_duty);
  PWM_setDuty(pwm_srv1, (fan_speed > 0) ? valve_open : valve_closed);
}

static void fanbee_updateOnOff() {
  if (nvm->writeItem) {
    nvm->writeItem(nvOnOffId, sizeof(fanbee_OnOff_OnOff), &fanbee_OnOff_OnOff);
  }
  zstack_bdbRepChangedAttrValueReq_t req = {
      .attrID = ATTRID_ON_OFF_ON_OFF,
      .cluster = ZCL_CLUSTER_ID_GENERAL_ON_OFF,
      .endpoint = FANBEE_ENDPOINT,
  };
  Zstackapi_bdbRepChangedAttrValueReq(sampleApp_serviceTaskId, &req);
}

static void fanbee_updateLevel() {
  if (nvm->writeItem) {
    nvm->writeItem(nvCurrentLevelId, sizeof(fanbee_Level_CurrentLevel), &fanbee_Level_CurrentLevel);
  }
  zstack_bdbRepChangedAttrValueReq_t req = {
      .attrID = ATTRID_LEVEL_CURRENT_LEVEL,
      .cluster = ZCL_CLUSTER_ID_GENERAL_LEVEL_CONTROL,
      .endpoint = FANBEE_ENDPOINT,
  };
  Zstackapi_bdbRepChangedAttrValueReq(sampleApp_serviceTaskId, &req);
}

// Initialization function for the zclGeneral layer.
static void fanbee_initZCLGeneral(void) {
  zclConfigInit();

#if defined(OTA_CLIENT_INTEGRATED)
  // Initialize OTA client
  otaClient_SetEndpoint(FANBEE_ENDPOINT);
  otaClient_setAttributes(fanbee_Attrs, fanbee_zclAttrsArraySize);
  zclOTA_setAttributes(fanbee_Attrs, fanbee_zclAttrsArraySize);

  otaClient_Init(appSemHandle, sampleApp_serviceTaskId, 0);
#endif
  // Register the Application to receive the unprocessed Foundation command/response messages
  zclport_registerZclHandleExternal(FANBEE_ENDPOINT, fanbee_ProcessIncomingMsg);

  // Write the bdb initialization parameters
  zstack_bdbSetAttributesReq_t zstack_bdbSetAttrReq;

  zstack_bdbSetAttrReq.bdbCommissioningGroupID = BDB_DEFAULT_COMMISSIONING_GROUP_ID;
  zstack_bdbSetAttrReq.bdbPrimaryChannelSet = BDB_DEFAULT_PRIMARY_CHANNEL_SET;
  zstack_bdbSetAttrReq.bdbScanDuration = BDB_DEFAULT_SCAN_DURATION;
  zstack_bdbSetAttrReq.bdbSecondaryChannelSet = BDB_DEFAULT_SECONDARY_CHANNEL_SET;
  zstack_bdbSetAttrReq.has_bdbCommissioningGroupID = TRUE;
  zstack_bdbSetAttrReq.has_bdbPrimaryChannelSet = TRUE;
  zstack_bdbSetAttrReq.has_bdbScanDuration = TRUE;
  zstack_bdbSetAttrReq.has_bdbSecondaryChannelSet = TRUE;
  zstack_bdbSetAttrReq.has_bdbTCLinkKeyExchangeAttemptsMax = TRUE;
  zstack_bdbSetAttrReq.has_bdbTCLinkKeyExchangeMethod = TRUE;
  zstack_bdbSetAttrReq.bdbTCLinkKeyExchangeAttemptsMax =
      BDB_DEFAULT_TC_LINK_KEY_EXCHANGE_ATTEMPS_MAX;
  zstack_bdbSetAttrReq.bdbTCLinkKeyExchangeMethod = BDB_DEFAULT_TC_LINK_KEY_EXCHANGE_METHOD;

  Zstackapi_bdbSetAttributesReq(sampleApp_serviceTaskId, &zstack_bdbSetAttrReq);

  // Register for Callbacks, turn on:
  //  Device State Change,
  //  ZDO Match Descriptor Response,
  zstack_devZDOCBReq_t zdoCBReq = {0};
  zdoCBReq.has_devStateChange = true;
  zdoCBReq.devStateChange = true;

  Zstackapi_DevZDOCBReq(sampleApp_serviceTaskId, &zdoCBReq);

  // Start BDB commissioning initialization
  zstack_bdbStartCommissioningReq_t zstack_bdbStartCommissioningReq;
  zstack_bdbStartCommissioningReq.commissioning_mode =
      BDB_COMMISSIONING_REJOIN_EXISTING_NETWORK_ON_STARTUP;
  Zstackapi_bdbStartCommissioningReq(sampleApp_serviceTaskId, &zstack_bdbStartCommissioningReq);
}

// Callback in which the status of the commissioning process are reported (Context message of the
// status of a commissioning process)
static void fanbee_ProcessCommissioningStatus(bdbCommissioningModeMsg_t *bdbCommissioningModeMsg) {
  Display_printf(debug_display_handle, 0, 0, "Commissioning mode %d Status %d",
                 bdbCommissioningModeMsg->bdbCommissioningMode, bdbCommissioningModeMsg->bdbCommissioningStatus);

  switch (bdbCommissioningModeMsg->bdbCommissioningMode) {
    case BDB_COMMISSIONING_INITIALIZATION:
    case BDB_COMMISSIONING_NWK_STEERING:
      switch (bdbCommissioningModeMsg->bdbCommissioningStatus) {
        case BDB_COMMISSIONING_SUCCESS:
        case BDB_COMMISSIONING_NETWORK_RESTORED:
          LED_stopBlinking(act_led_handle);
          joined = true;
          break;
        case BDB_COMMISSIONING_NO_NETWORK:
        case BDB_COMMISSIONING_TCLK_EX_FAILURE:
        case BDB_COMMISSIONING_FAILURE:
          LED_startBlinking(act_led_handle, 2000, LED_BLINK_FOREVER);
          break;
      }
      break;
  }
}

// Process ZCL Foundation incoming message
static uint8_t fanbee_ProcessIncomingMsg(zclIncoming_t *pInMsg) {
  uint8_t handled = FALSE;

  switch (pInMsg->hdr.commandID) {
    case ZCL_CMD_READ_RSP:
    case ZCL_CMD_WRITE_RSP:
    case ZCL_CMD_DEFAULT_RSP:
    case ZCL_CMD_DISCOVER_CMDS_RECEIVED_RSP:
    case ZCL_CMD_DISCOVER_CMDS_GEN_RSP:
    case ZCL_CMD_DISCOVER_ATTRS_RSP:
    case ZCL_CMD_DISCOVER_ATTRS_EXT_RSP:
      handled = TRUE;
      break;
    default:
      break;
  }

  if (pInMsg->attrCmd) MAP_osal_mem_free(pInMsg->attrCmd);

  return handled;
}

void rfDriverCallbackAntennaSwitching(RF_Handle client, RF_GlobalEvent events, void *arg) {
  // Switch off all paths
  GPIO_write(CONFIG_RF_24GHZ, 0);
  GPIO_write(CONFIG_RF_HIGH_PA, 0);

  if (events & RF_GlobalEventRadioSetup) {
    RF_TxPowerTable_PAType paType = (RF_TxPowerTable_PAType)RF_getTxPower(client).paType;
    if (paType == RF_TxPowerTable_HighPA) {
      GPIO_setMux(CONFIG_RF_24GHZ, IOC_PORT_RFC_GPO0);
      /* Note: RFC_GPO3 is a work-around because the RFC_GPO1 (PA enable signal) is sometimes not
                de-asserted on CC1352 Rev A. */
      GPIO_setMux(CONFIG_RF_HIGH_PA, IOC_PORT_RFC_GPO3);
    } else {
      // RF core active --> 2.4 GHz
      GPIO_setMux(CONFIG_RF_24GHZ, IOC_PORT_GPIO);
      GPIO_setMux(CONFIG_RF_HIGH_PA, IOC_PORT_GPIO);
      GPIO_write(CONFIG_RF_24GHZ, 1);
    }
  } else {
    // Reset the IO multiplexer to GPIO functionality
    GPIO_setMux(CONFIG_RF_24GHZ, IOC_PORT_GPIO);
    GPIO_setMux(CONFIG_RF_HIGH_PA, IOC_PORT_GPIO);
  }
}
