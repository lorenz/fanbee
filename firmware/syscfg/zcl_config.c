#include "zcl_config.h"

#include "zstackapi.h"

/*********************************************************************
 * Application Globals
 *********************************************************************/
WEAK uint8_t sampleApp_serviceTaskId;

static endPointDesc_t fanbeeEpDesc = {0};

/*********************************************************************
 * ZCL Attribute Variables
 *********************************************************************/

// Basic Cluster (Server-Side)
WEAK uint8 fanbee_Basic_ZCLVersion;
WEAK uint8 fanbee_Basic_ApplicationVersion;
WEAK uint8 fanbee_Basic_ManufacturerName[];
WEAK uint8 fanbee_Basic_ModelIdentifier[];
WEAK enum8 fanbee_Basic_PowerSource;
WEAK uint16 fanbee_Basic_ClusterRevision;

// Identify Cluster (Server-Side)
WEAK uint16 fanbee_Identify_IdentifyTime;
WEAK uint16 fanbee_Identify_ClusterRevision;

// Groups Cluster (Server-Side)
WEAK map8 fanbee_Groups_NameSupport;
WEAK uint16 fanbee_Groups_ClusterRevision;

// Scenes Cluster (Server-Side)
WEAK uint8 fanbee_Scenes_SceneCount;
WEAK uint8 fanbee_Scenes_CurrentScene;
WEAK SGroupId fanbee_Scenes_CurrentGroup;
WEAK bool fanbee_Scenes_SceneValid;
WEAK map8 fanbee_Scenes_NameSupport;
WEAK uint16 fanbee_Scenes_ClusterRevision;

// OnOff Cluster (Server-Side)
WEAK bool fanbee_OnOff_OnOff;
WEAK uint16 fanbee_OnOff_ClusterRevision;

// Level Cluster (Server-Side)
WEAK uint8 fanbee_Level_CurrentLevel;
WEAK uint8 fanbee_Level_MinLevel;
WEAK uint8 fanbee_Level_MaxLevel;
WEAK uint16 fanbee_Level_ClusterRevision;

/*********************************************************************
 * ZCL Attribute List
 *********************************************************************/
// NOTE: The attributes listed in the AttrRec must be in ascending order
// per cluster to allow right function of the Foundation discovery commands
const zclAttrRec_t fanbee_Attrs[] = {
#ifdef ZCL_BASIC
    {ZCL_CLUSTER_ID_GENERAL_BASIC,
     {ATTRID_BASIC_ZCL_VERSION, ZCL_DATATYPE_UINT8,
      (ACCESS_CONTROL_READ | ACCESS_CONTROL_AUTH_READ), (void *)&fanbee_Basic_ZCLVersion}},
    {ZCL_CLUSTER_ID_GENERAL_BASIC,
     {ATTRID_BASIC_APPLICATION_VERSION, ZCL_DATATYPE_UINT8,
      (ACCESS_CONTROL_READ | ACCESS_CONTROL_AUTH_READ), (void *)&fanbee_Basic_ApplicationVersion}},
    {ZCL_CLUSTER_ID_GENERAL_BASIC,
     {ATTRID_BASIC_MANUFACTURER_NAME, ZCL_DATATYPE_CHAR_STR,
      (ACCESS_CONTROL_READ | ACCESS_CONTROL_AUTH_READ), (void *)&fanbee_Basic_ManufacturerName}},
    {ZCL_CLUSTER_ID_GENERAL_BASIC,
     {ATTRID_BASIC_MODEL_IDENTIFIER, ZCL_DATATYPE_CHAR_STR,
      (ACCESS_CONTROL_READ | ACCESS_CONTROL_AUTH_READ), (void *)&fanbee_Basic_ModelIdentifier}},
    {ZCL_CLUSTER_ID_GENERAL_BASIC,
     {ATTRID_BASIC_POWER_SOURCE, ZCL_DATATYPE_ENUM8,
      (ACCESS_CONTROL_READ | ACCESS_CONTROL_AUTH_READ), (void *)&fanbee_Basic_PowerSource}},
    {ZCL_CLUSTER_ID_GENERAL_BASIC,
     {ATTRID_CLUSTER_REVISION, ZCL_DATATYPE_UINT16,
      (ACCESS_CONTROL_READ | ACCESS_CONTROL_AUTH_READ), (void *)&fanbee_Basic_ClusterRevision}},
#endif
#ifdef ZCL_IDENTIFY
    {ZCL_CLUSTER_ID_GENERAL_IDENTIFY,
     {ATTRID_IDENTIFY_IDENTIFY_TIME, ZCL_DATATYPE_UINT16,
      (ACCESS_CONTROL_WRITE | ACCESS_CONTROL_AUTH_WRITE) |
          (ACCESS_CONTROL_READ | ACCESS_CONTROL_AUTH_READ),
      (void *)&fanbee_Identify_IdentifyTime}},
    {ZCL_CLUSTER_ID_GENERAL_IDENTIFY,
     {ATTRID_CLUSTER_REVISION, ZCL_DATATYPE_UINT16,
      (ACCESS_CONTROL_READ | ACCESS_CONTROL_AUTH_READ), (void *)&fanbee_Identify_ClusterRevision}},
#endif
#ifdef ZCL_GROUPS
    {ZCL_CLUSTER_ID_GENERAL_GROUPS,
     {ATTRID_GROUPS_NAME_SUPPORT, ZCL_DATATYPE_BITMAP8,
      (ACCESS_CONTROL_READ | ACCESS_CONTROL_AUTH_READ), (void *)&fanbee_Groups_NameSupport}},
    {ZCL_CLUSTER_ID_GENERAL_GROUPS,
     {ATTRID_CLUSTER_REVISION, ZCL_DATATYPE_UINT16,
      (ACCESS_CONTROL_READ | ACCESS_CONTROL_AUTH_READ), (void *)&fanbee_Groups_ClusterRevision}},
#endif
#ifdef ZCL_SCENES
    {ZCL_CLUSTER_ID_GENERAL_SCENES,
     {ATTRID_SCENES_SCENE_COUNT, ZCL_DATATYPE_UINT8,
      (ACCESS_CONTROL_READ | ACCESS_CONTROL_AUTH_READ), (void *)&fanbee_Scenes_SceneCount}},
    {ZCL_CLUSTER_ID_GENERAL_SCENES,
     {ATTRID_SCENES_CURRENT_SCENE, ZCL_DATATYPE_UINT8,
      (ACCESS_CONTROL_READ | ACCESS_CONTROL_AUTH_READ), (void *)&fanbee_Scenes_CurrentScene}},
    {ZCL_CLUSTER_ID_GENERAL_SCENES,
     {ATTRID_SCENES_CURRENT_GROUP, ZCL_DATATYPE_UINT16,
      (ACCESS_CONTROL_READ | ACCESS_CONTROL_AUTH_READ), (void *)&fanbee_Scenes_CurrentGroup}},
    {ZCL_CLUSTER_ID_GENERAL_SCENES,
     {ATTRID_SCENES_SCENE_VALID, ZCL_DATATYPE_BOOLEAN,
      (ACCESS_CONTROL_READ | ACCESS_CONTROL_AUTH_READ), (void *)&fanbee_Scenes_SceneValid}},
    {ZCL_CLUSTER_ID_GENERAL_SCENES,
     {ATTRID_SCENES_NAME_SUPPORT, ZCL_DATATYPE_BITMAP8,
      (ACCESS_CONTROL_READ | ACCESS_CONTROL_AUTH_READ), (void *)&fanbee_Scenes_NameSupport}},
    {ZCL_CLUSTER_ID_GENERAL_SCENES,
     {ATTRID_CLUSTER_REVISION, ZCL_DATATYPE_UINT16,
      (ACCESS_CONTROL_READ | ACCESS_CONTROL_AUTH_READ), (void *)&fanbee_Scenes_ClusterRevision}},
#endif
#ifdef ZCL_ON_OFF
    {ZCL_CLUSTER_ID_GENERAL_ON_OFF,
     {ATTRID_ON_OFF_ON_OFF, ZCL_DATATYPE_BOOLEAN,
      ACCESS_REPORTABLE | (ACCESS_CONTROL_READ | ACCESS_CONTROL_AUTH_READ),
      (void *)&fanbee_OnOff_OnOff}},
    {ZCL_CLUSTER_ID_GENERAL_ON_OFF,
     {ATTRID_CLUSTER_REVISION, ZCL_DATATYPE_UINT16,
      (ACCESS_CONTROL_READ | ACCESS_CONTROL_AUTH_READ), (void *)&fanbee_OnOff_ClusterRevision}},
#endif
#ifdef ZCL_LEVEL_CTRL
    {ZCL_CLUSTER_ID_GENERAL_LEVEL_CONTROL,
     {ATTRID_LEVEL_CURRENT_LEVEL, ZCL_DATATYPE_UINT8,
      ACCESS_REPORTABLE | (ACCESS_CONTROL_READ | ACCESS_CONTROL_AUTH_READ),
      (void *)&fanbee_Level_CurrentLevel}},
    {ZCL_CLUSTER_ID_GENERAL_LEVEL_CONTROL,
     {ATTRID_LEVEL_MIN_LEVEL, ZCL_DATATYPE_UINT8, (ACCESS_CONTROL_READ | ACCESS_CONTROL_AUTH_READ),
      (void *)&fanbee_Level_MinLevel}},
    {ZCL_CLUSTER_ID_GENERAL_LEVEL_CONTROL,
     {ATTRID_LEVEL_MAX_LEVEL, ZCL_DATATYPE_UINT8, (ACCESS_CONTROL_READ | ACCESS_CONTROL_AUTH_READ),
      (void *)&fanbee_Level_MaxLevel}},
    {ZCL_CLUSTER_ID_GENERAL_LEVEL_CONTROL,
     {ATTRID_CLUSTER_REVISION, ZCL_DATATYPE_UINT16,
      (ACCESS_CONTROL_READ | ACCESS_CONTROL_AUTH_READ), (void *)&fanbee_Level_ClusterRevision}},
#endif
};

const uint8_t fanbee_zclAttrsArraySize = (sizeof(fanbee_Attrs) / sizeof(fanbee_Attrs[0]));

/*********************************************************************
 * ZCL Attribute Default Values (const)
 *********************************************************************/
WEAK const uint8 DEFAULT_FANBEE_BASIC_ZCL_VERSION = 3;
WEAK const uint8 DEFAULT_FANBEE_BASIC_APPLICATION_VERSION = 0;
WEAK const enum8 DEFAULT_FANBEE_BASIC_POWER_SOURCE = 0;
WEAK const uint16 DEFAULT_FANBEE_BASIC_CLUSTER_REVISION = 1;
WEAK const uint16 DEFAULT_FANBEE_IDENTIFY_IDENTIFY_TIME = 0;
WEAK const uint16 DEFAULT_FANBEE_IDENTIFY_CLUSTER_REVISION = 1;
WEAK const uint16 DEFAULT_FANBEE_GROUPS_CLUSTER_REVISION = 1;
WEAK const uint8 DEFAULT_FANBEE_SCENES_SCENE_COUNT = 0;
WEAK const uint8 DEFAULT_FANBEE_SCENES_CURRENT_SCENE = 0;
WEAK const SGroupId DEFAULT_FANBEE_SCENES_CURRENT_GROUP = 0;
WEAK const bool DEFAULT_FANBEE_SCENES_SCENE_VALID = 0;
WEAK const uint16 DEFAULT_FANBEE_SCENES_CLUSTER_REVISION = 1;
WEAK const bool DEFAULT_FANBEE_ON_OFF_ON_OFF = 0;
WEAK const uint16 DEFAULT_FANBEE_ONOFF_CLUSTER_REVISION = 1;
WEAK const uint8 DEFAULT_FANBEE_LEVEL_CURRENT_LEVEL = 255;
WEAK const uint8 DEFAULT_FANBEE_LEVEL_MIN_LEVEL = 0;
WEAK const uint8 DEFAULT_FANBEE_LEVEL_MAX_LEVEL = 255;
WEAK const uint16 DEFAULT_FANBEE_LEVEL_CLUSTER_REVISION = 1;

/*********************************************************************
 * ZCL Attribute Reset Functionality
 *********************************************************************/
void fanbee_ResetAttributesToDefaultValues(void) {
  fanbee_Basic_ZCLVersion = DEFAULT_FANBEE_BASIC_ZCL_VERSION;
  fanbee_Basic_ApplicationVersion = DEFAULT_FANBEE_BASIC_APPLICATION_VERSION;
  fanbee_Basic_PowerSource = DEFAULT_FANBEE_BASIC_POWER_SOURCE;
  fanbee_Basic_ClusterRevision = DEFAULT_FANBEE_BASIC_CLUSTER_REVISION;
  fanbee_Identify_IdentifyTime = DEFAULT_FANBEE_IDENTIFY_IDENTIFY_TIME;
  fanbee_Identify_ClusterRevision = DEFAULT_FANBEE_IDENTIFY_CLUSTER_REVISION;
  fanbee_Groups_ClusterRevision = DEFAULT_FANBEE_GROUPS_CLUSTER_REVISION;
  fanbee_Scenes_SceneCount = DEFAULT_FANBEE_SCENES_SCENE_COUNT;
  fanbee_Scenes_CurrentScene = DEFAULT_FANBEE_SCENES_CURRENT_SCENE;
  fanbee_Scenes_CurrentGroup = DEFAULT_FANBEE_SCENES_CURRENT_GROUP;
  fanbee_Scenes_SceneValid = DEFAULT_FANBEE_SCENES_SCENE_VALID;
  fanbee_Scenes_ClusterRevision = DEFAULT_FANBEE_SCENES_CLUSTER_REVISION;
  fanbee_OnOff_OnOff = DEFAULT_FANBEE_ON_OFF_ON_OFF;
  fanbee_OnOff_ClusterRevision = DEFAULT_FANBEE_ONOFF_CLUSTER_REVISION;
  fanbee_Level_CurrentLevel = DEFAULT_FANBEE_LEVEL_CURRENT_LEVEL;
  fanbee_Level_MinLevel = DEFAULT_FANBEE_LEVEL_MIN_LEVEL;
  fanbee_Level_MaxLevel = DEFAULT_FANBEE_LEVEL_MAX_LEVEL;
  fanbee_Level_ClusterRevision = DEFAULT_FANBEE_LEVEL_CLUSTER_REVISION;
}

/*********************************************************************
 * ZCL Commands List
 *********************************************************************/
const zclCommandRec_t fanbee_Cmds[] = {
#ifdef ZCL_BASIC
#endif
#ifdef ZCL_IDENTIFY
    {
        ZCL_CLUSTER_ID_GENERAL_IDENTIFY,
        COMMAND_IDENTIFY_IDENTIFY_QUERY_RESPONSE,
        CMD_DIR_SERVER_GENERATED,
    },
    {
        ZCL_CLUSTER_ID_GENERAL_IDENTIFY,
        COMMAND_IDENTIFY_IDENTIFY,
        CMD_DIR_SERVER_RECEIVED,
    },
    {
        ZCL_CLUSTER_ID_GENERAL_IDENTIFY,
        COMMAND_IDENTIFY_IDENTIFY_QUERY,
        CMD_DIR_SERVER_RECEIVED,
    },
#endif
#ifdef ZCL_GROUPS
    {
        ZCL_CLUSTER_ID_GENERAL_GROUPS,
        COMMAND_GROUPS_ADD_GROUP_RESPONSE,
        CMD_DIR_SERVER_GENERATED,
    },
    {
        ZCL_CLUSTER_ID_GENERAL_GROUPS,
        COMMAND_GROUPS_VIEW_GROUP_RESPONSE,
        CMD_DIR_SERVER_GENERATED,
    },
    {
        ZCL_CLUSTER_ID_GENERAL_GROUPS,
        COMMAND_GROUPS_GET_GROUP_MEMBERSHIP_RESPONSE,
        CMD_DIR_SERVER_GENERATED,
    },
    {
        ZCL_CLUSTER_ID_GENERAL_GROUPS,
        COMMAND_GROUPS_REMOVE_GROUP_RESPONSE,
        CMD_DIR_SERVER_GENERATED,
    },
    {
        ZCL_CLUSTER_ID_GENERAL_GROUPS,
        COMMAND_GROUPS_ADD_GROUP,
        CMD_DIR_SERVER_RECEIVED,
    },
    {
        ZCL_CLUSTER_ID_GENERAL_GROUPS,
        COMMAND_GROUPS_VIEW_GROUP,
        CMD_DIR_SERVER_RECEIVED,
    },
    {
        ZCL_CLUSTER_ID_GENERAL_GROUPS,
        COMMAND_GROUPS_GET_GROUP_MEMBERSHIP,
        CMD_DIR_SERVER_RECEIVED,
    },
    {
        ZCL_CLUSTER_ID_GENERAL_GROUPS,
        COMMAND_GROUPS_REMOVE_GROUP,
        CMD_DIR_SERVER_RECEIVED,
    },
    {
        ZCL_CLUSTER_ID_GENERAL_GROUPS,
        COMMAND_GROUPS_REMOVE_ALL_GROUPS,
        CMD_DIR_SERVER_RECEIVED,
    },
    {
        ZCL_CLUSTER_ID_GENERAL_GROUPS,
        COMMAND_GROUPS_ADD_GROUP_IF_IDENTIFYING,
        CMD_DIR_SERVER_RECEIVED,
    },
#endif
#ifdef ZCL_SCENES
    {
        ZCL_CLUSTER_ID_GENERAL_SCENES,
        COMMAND_SCENES_ADD_SCENE_RESPONSE,
        CMD_DIR_SERVER_GENERATED,
    },
    {
        ZCL_CLUSTER_ID_GENERAL_SCENES,
        COMMAND_SCENES_VIEW_SCENE_RESPONSE,
        CMD_DIR_SERVER_GENERATED,
    },
    {
        ZCL_CLUSTER_ID_GENERAL_SCENES,
        COMMAND_SCENES_REMOVE_SCENE_RESPONSE,
        CMD_DIR_SERVER_GENERATED,
    },
    {
        ZCL_CLUSTER_ID_GENERAL_SCENES,
        COMMAND_SCENES_REMOVE_ALL_SCENES_RESPONSE,
        CMD_DIR_SERVER_GENERATED,
    },
    {
        ZCL_CLUSTER_ID_GENERAL_SCENES,
        COMMAND_SCENES_STORE_SCENE_RESPONSE,
        CMD_DIR_SERVER_GENERATED,
    },
    {
        ZCL_CLUSTER_ID_GENERAL_SCENES,
        COMMAND_SCENES_GET_SCENE_MEMBERSHIP_RESPONSE,
        CMD_DIR_SERVER_GENERATED,
    },
    {
        ZCL_CLUSTER_ID_GENERAL_SCENES,
        COMMAND_SCENES_ADD_SCENE,
        CMD_DIR_SERVER_RECEIVED,
    },
    {
        ZCL_CLUSTER_ID_GENERAL_SCENES,
        COMMAND_SCENES_VIEW_SCENE,
        CMD_DIR_SERVER_RECEIVED,
    },
    {
        ZCL_CLUSTER_ID_GENERAL_SCENES,
        COMMAND_SCENES_REMOVE_SCENE,
        CMD_DIR_SERVER_RECEIVED,
    },
    {
        ZCL_CLUSTER_ID_GENERAL_SCENES,
        COMMAND_SCENES_REMOVE_ALL_SCENES,
        CMD_DIR_SERVER_RECEIVED,
    },
    {
        ZCL_CLUSTER_ID_GENERAL_SCENES,
        COMMAND_SCENES_STORE_SCENE,
        CMD_DIR_SERVER_RECEIVED,
    },
    {
        ZCL_CLUSTER_ID_GENERAL_SCENES,
        COMMAND_SCENES_RECALL_SCENE,
        CMD_DIR_SERVER_RECEIVED,
    },
    {
        ZCL_CLUSTER_ID_GENERAL_SCENES,
        COMMAND_SCENES_GET_SCENE_MEMBERSHIP,
        CMD_DIR_SERVER_RECEIVED,
    },
#endif
#ifdef ZCL_ON_OFF
    {
        ZCL_CLUSTER_ID_GENERAL_ON_OFF,
        COMMAND_ON_OFF_OFF,
        CMD_DIR_SERVER_RECEIVED,
    },
    {
        ZCL_CLUSTER_ID_GENERAL_ON_OFF,
        COMMAND_ON_OFF_ON,
        CMD_DIR_SERVER_RECEIVED,
    },
    {
        ZCL_CLUSTER_ID_GENERAL_ON_OFF,
        COMMAND_ON_OFF_TOGGLE,
        CMD_DIR_SERVER_RECEIVED,
    },
#endif
#ifdef ZCL_LEVEL_CTRL
    {
        ZCL_CLUSTER_ID_GENERAL_LEVEL_CONTROL,
        COMMAND_LEVEL_MOVE_TO_LEVEL,
        CMD_DIR_SERVER_RECEIVED,
    },
    {
        ZCL_CLUSTER_ID_GENERAL_LEVEL_CONTROL,
        COMMAND_LEVEL_MOVE,
        CMD_DIR_SERVER_RECEIVED,
    },
    {
        ZCL_CLUSTER_ID_GENERAL_LEVEL_CONTROL,
        COMMAND_LEVEL_STEP,
        CMD_DIR_SERVER_RECEIVED,
    },
    {
        ZCL_CLUSTER_ID_GENERAL_LEVEL_CONTROL,
        COMMAND_LEVEL_STOP,
        CMD_DIR_SERVER_RECEIVED,
    },
    {
        ZCL_CLUSTER_ID_GENERAL_LEVEL_CONTROL,
        COMMAND_LEVEL_MOVE_TO_LEVEL_WITH_ON_OFF,
        CMD_DIR_SERVER_RECEIVED,
    },
    {
        ZCL_CLUSTER_ID_GENERAL_LEVEL_CONTROL,
        COMMAND_LEVEL_MOVE_WITH_ON_OFF,
        CMD_DIR_SERVER_RECEIVED,
    },
    {
        ZCL_CLUSTER_ID_GENERAL_LEVEL_CONTROL,
        COMMAND_LEVEL_STEP_WITH_ON_OFF,
        CMD_DIR_SERVER_RECEIVED,
    },
    {
        ZCL_CLUSTER_ID_GENERAL_LEVEL_CONTROL,
        COMMAND_LEVEL_STOP_WITH_ON_OFF,
        CMD_DIR_SERVER_RECEIVED,
    },
#endif
};

const uint8_t fanbee_zclCmdsArraySize = (sizeof(fanbee_Cmds) / sizeof(fanbee_Cmds[0]));

/*********************************************************************
 * ZCL Command Callback Structs
 *********************************************************************/

zclGeneral_AppCallbacks_t fanbee_zclGeneralCmdCallbacks = {
    NULL,
    fanbee_IdentifyCB,
    fanbee_IdentifyQueryCB,
    NULL,
    NULL,
#ifdef ZCL_ON_OFF
    fanbee_OnOffCB,
    NULL,
    NULL,
    NULL,
#endif
#ifdef ZCL_LEVEL_CTRL
    fanbee_LevelControlMoveToLevelCB,
    fanbee_LevelControlMoveCB,
    fanbee_LevelControlStepCB,
    fanbee_LevelControlStopCB,
    NULL,
#endif
#ifdef ZCL_GROUPS
    NULL,
#endif
#ifdef ZCL_SCENES
    fanbee_SceneStoreReqCB,
    fanbee_SceneRecallReqCB,
    NULL,
#endif
#ifdef ZCL_ALARMS
    NULL,
#endif
#ifdef SE_UK_EXT
    NULL,
    NULL,
#endif
    NULL,
    NULL,
};

/*********************************************************************
 * ZCL Command Callbacks
 *********************************************************************/

/* GENERAL */
/// This callback is called to process an incoming Identify command.
WEAK void fanbee_IdentifyCB(zclIdentify_t *pCmd) {}
/// This callback is called to process an incoming Identify Query command.
WEAK void fanbee_IdentifyQueryCB(zclIdentifyQuery_t *pCmd) {}
/// This callback is called to process an incoming On, Off or Toggle command.
WEAK void fanbee_OnOffCB(uint8_t cmd) {}
/// This callback is called to process a Level Control - Move to Level command
WEAK void fanbee_LevelControlMoveToLevelCB(zclLCMoveToLevel_t *pCmd) {}
/// This callback is called to process a Level Control - Move command
WEAK void fanbee_LevelControlMoveCB(zclLCMove_t *pCmd) {}
/// This callback is called to process a Level Control - Step command
WEAK void fanbee_LevelControlStepCB(zclLCStep_t *pCmd) {}
/// This callback is called to process a Level Control - Stop command
WEAK void fanbee_LevelControlStopCB(zclLCStop_t *pCmd) {}
/// This callback is called to process an incoming Scene Store request.
/// The app will fill in the 'extField' with what is needed to restore its
/// current settings. Before overwriting the content of the scene,
/// App needs to verify if there was a change with the previous configuration.
/// App function returns TRUE if there was a change, otherwise returns FALSE.
WEAK uint8_t fanbee_SceneStoreReqCB(zclSceneReq_t *pReq) { return ((uint8_t)0); }
/// This callback is called to process an incoming Scene Recall request
/// The app will use what's in the 'extField' to restore to these settings.
WEAK void fanbee_SceneRecallReqCB(zclSceneReq_t *pReq) {}

/*********************************************************************
 * Simple Descriptor
 *********************************************************************/
WEAK uint8_t fanbee_Device_Version = FANBEE_DEVICE_VERSION;

WEAK uint8_t fanbee_Flags = FANBEE_FLAGS;

WEAK uint8_t fanbee_EndPoint = FANBEE_ENDPOINT;

const cId_t fanbee_InClusterList[] = {
    ZCL_CLUSTER_ID_GENERAL_BASIC,  ZCL_CLUSTER_ID_GENERAL_IDENTIFY,
    ZCL_CLUSTER_ID_GENERAL_GROUPS, ZCL_CLUSTER_ID_GENERAL_SCENES,
    ZCL_CLUSTER_ID_GENERAL_ON_OFF, ZCL_CLUSTER_ID_GENERAL_LEVEL_CONTROL,
};

#define FANBEE_MAX_INCLUSTERS (sizeof(fanbee_InClusterList) / sizeof(fanbee_InClusterList[0]))

SimpleDescriptionFormat_t fanbee_SimpleDesc = {
    FANBEE_ENDPOINT,                         //  int EndPoint
    ZCL_HA_PROFILE_ID,                       //  uint16_t AppProfId[2]
    ZCL_DEVICEID_LEVEL_CONTROLLABLE_OUTPUT,  //  uint16_t AppDeviceId[2];
    FANBEE_DEVICE_VERSION,                   //  int   AppDevVer:4;
    FANBEE_FLAGS,                            //  int   AppFlags:4;
    FANBEE_MAX_INCLUSTERS,                   //  byte  AppNumInClusters;
    (cId_t *)fanbee_InClusterList,           //  byte *pAppInClusterList;
    0,                                       //  byte  AppNumOutClusters;
    NULL                                     //  byte *pAppOutClusterList;
};

/*********************************************************************
 * ZCL Initialization Hooks
 *********************************************************************/
#ifdef ZCL_DIAGNOSTIC
// Register the application's callback function to read/write attribute data.
// This is only required when the attribute data format is unknown to ZCL.
zcl_registerReadWriteCB(FANBEE_ENDPOINT, zclDiagnostic_ReadWriteAttrCB, NULL);

#endif

/*********************************************************************
 * @fn          zclConfigInit
 *
 * @brief       This is called to initialize the statically-generated
 *              SysConfig ZCL code. This API should not be modified by
 *              the user.
 *
 * @param       none
 *
 * @return      none
 *********************************************************************/
void zclConfigInit(void) {
  // register endpoint with ZCL
  fanbeeEpDesc.endPoint = fanbee_EndPoint;
  fanbeeEpDesc.simpleDesc = &fanbee_SimpleDesc;
  zclport_registerEndpoint(sampleApp_serviceTaskId, &fanbeeEpDesc);

  // register the applications attribute list with ZCL
  zcl_registerAttrList(fanbee_EndPoint, fanbee_zclAttrsArraySize, fanbee_Attrs);

  // reset attributes to their default values
  fanbee_ResetAttributesToDefaultValues();

#ifdef ZCL_DISCOVER
  // register the applications command list with ZCL
  zcl_registerCmdList(fanbee_EndPoint, fanbee_zclCmdsArraySize, fanbee_Cmds);

#endif

  zclGeneral_RegisterCmdCallbacks(FANBEE_ENDPOINT, &fanbee_zclGeneralCmdCallbacks);

#ifdef BDB_REPORTING
  zstack_bdbRepAddAttrCfgRecordDefaultToListReq_t Req = {0};
  struct foo {
    uint8_t arr[BDBREPORTING_MAX_ANALOG_ATTR_SIZE];
  };
  struct foo foo;
#ifdef ZCL_ON_OFF
  foo = (struct foo){.arr = {0x00, 0x00, 0x00, 0x00}};
  Req.attrID = ATTRID_ON_OFF_ON_OFF;
  Req.cluster = ZCL_CLUSTER_ID_GENERAL_ON_OFF;
  Req.endpoint = FANBEE_ENDPOINT;
  Req.maxReportInt = 0x0000;
  Req.minReportInt = 0x0000;
  OsalPort_memcpy(Req.reportableChange, foo.arr, BDBREPORTING_MAX_ANALOG_ATTR_SIZE);
  Zstackapi_bdbRepAddAttrCfgRecordDefaultToListReq(sampleApp_serviceTaskId, &Req);

#endif
#ifdef ZCL_LEVEL_CTRL
  foo = (struct foo){.arr = {0x00, 0x00, 0x00, 0x00}};
  Req.attrID = ATTRID_LEVEL_CURRENT_LEVEL;
  Req.cluster = ZCL_CLUSTER_ID_GENERAL_LEVEL_CONTROL;
  Req.endpoint = FANBEE_ENDPOINT;
  Req.maxReportInt = 0x0000;
  Req.minReportInt = 0x0000;
  OsalPort_memcpy(Req.reportableChange, foo.arr, BDBREPORTING_MAX_ANALOG_ATTR_SIZE);
  Zstackapi_bdbRepAddAttrCfgRecordDefaultToListReq(sampleApp_serviceTaskId, &Req);

#endif

#endif
}
