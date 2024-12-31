/*
 *  ======== ti_drivers_config.c ========
 *  Configured TI-Drivers module definitions
 *
 *  DO NOT EDIT - This file is generated for the CC1352P1F3RGZ
 *  by the SysConfig tool.
 */

#include <stddef.h>
#include <stdint.h>

#ifndef DeviceFamily_CC13X2
#define DeviceFamily_CC13X2
#endif

#include <ti/devices/DeviceFamily.h>

#include "ti_drivers_config.h"

/*
 *  ============================= Display =============================
 */

#include <ti/display/Display.h>
#include <ti/display/DisplayUart2.h>

#define CONFIG_Display_COUNT 1


#define Display_UART2BUFFERSIZE 1024
static char displayUART2Buffer[Display_UART2BUFFERSIZE];

DisplayUart2_Object displayUart2Object;

const DisplayUart2_HWAttrs displayUart2HWAttrs = {
    .uartIdx      = CONFIG_UART,
    .baudRate     = 115200,
    .mutexTimeout = (unsigned int)(-1),
    .strBuf       = displayUART2Buffer,
    .strBufLen    = Display_UART2BUFFERSIZE
};

const Display_Config Display_config[CONFIG_Display_COUNT] = {
    /* CONFIG_DISPLAY_DEBUG */
    {
        .fxnTablePtr = &DisplayUart2Min_fxnTable,
        .object      = &displayUart2Object,
        .hwAttrs     = &displayUart2HWAttrs
    },
};

const uint_least8_t Display_count = CONFIG_Display_COUNT;

/*
 *  =============================== AESCBC ===============================
 */

#include <ti/drivers/AESCBC.h>
#include <ti/drivers/aescbc/AESCBCCC26XX.h>

#define CONFIG_AESCBC_COUNT 1


AESCBCCC26XX_Object aescbcCC26XXObjects[CONFIG_AESCBC_COUNT];

/*
 *  ======== aescbcCC26XXHWAttrs ========
 */
const AESCBCCC26XX_HWAttrs aescbcCC26XXHWAttrs[CONFIG_AESCBC_COUNT] = {
    {
        .intPriority = (~0),
    },
};

const AESCBC_Config AESCBC_config[CONFIG_AESCBC_COUNT] = {
    {   /* CONFIG_AESCBC_0 */
        .object  = &aescbcCC26XXObjects[CONFIG_AESCBC_0],
        .hwAttrs = &aescbcCC26XXHWAttrs[CONFIG_AESCBC_0]
    },
};

const uint_least8_t CONFIG_AESCBC_0_CONST = CONFIG_AESCBC_0;
const uint_least8_t AESCBC_count = CONFIG_AESCBC_COUNT;

/*
 *  =============================== AESCCM ===============================
 */

#include <ti/drivers/AESCCM.h>
#include <ti/drivers/aesccm/AESCCMCC26XX.h>

#define CONFIG_AESCCM_COUNT 1
AESCCMCC26XX_Object aesccmCC26XXObjects[CONFIG_AESCCM_COUNT];

/*
 *  ======== aesccmCC26XXHWAttrs ========
 */
const AESCCMCC26XX_HWAttrs aesccmCC26XXHWAttrs[CONFIG_AESCCM_COUNT] = {
    {
        .intPriority = 0x40,
    },
};

const AESCCM_Config AESCCM_config[CONFIG_AESCCM_COUNT] = {
    {   /* CONFIG_AESCCM_0 */
        .object  = &aesccmCC26XXObjects[CONFIG_AESCCM_0],
        .hwAttrs = &aesccmCC26XXHWAttrs[CONFIG_AESCCM_0]
    },
};

const uint_least8_t CONFIG_AESCCM_0_CONST = CONFIG_AESCCM_0;
const uint_least8_t AESCCM_count = CONFIG_AESCCM_COUNT;

/*
 *  =============================== AESECB ===============================
 */

#include <ti/drivers/AESECB.h>
#include <ti/drivers/aesecb/AESECBCC26XX.h>

#define CONFIG_AESECB_COUNT 1


AESECBCC26XX_Object aesecbCC26XXObjects[CONFIG_AESECB_COUNT];

/*
 *  ======== aesecbCC26XXHWAttrs ========
 */
const AESECBCC26XX_HWAttrs aesecbCC26XXHWAttrs[CONFIG_AESECB_COUNT] = {
    {
        .intPriority = 0x20,
    },
};

const AESECB_Config AESECB_config[CONFIG_AESECB_COUNT] = {
    {   /* CONFIG_AESECB_0 */
        .object  = &aesecbCC26XXObjects[CONFIG_AESECB_0],
        .hwAttrs = &aesecbCC26XXHWAttrs[CONFIG_AESECB_0]
    },
};


const uint_least8_t CONFIG_AESECB_0_CONST = CONFIG_AESECB_0;
const uint_least8_t AESECB_count = CONFIG_AESECB_COUNT;

/*
 *  =============================== DMA ===============================
 */

#include <ti/drivers/dma/UDMACC26XX.h>
#include <ti/devices/cc13x2_cc26x2/driverlib/udma.h>
#include <ti/devices/cc13x2_cc26x2/inc/hw_memmap.h>

UDMACC26XX_Object udmaCC26XXObject;

const UDMACC26XX_HWAttrs udmaCC26XXHWAttrs = {
    .baseAddr        = UDMA0_BASE,
    .powerMngrId     = PowerCC26XX_PERIPH_UDMA,
    .intNum          = INT_DMA_ERR,
    .intPriority     = (~0)
};

const UDMACC26XX_Config UDMACC26XX_config[1] = {
    {
        .object         = &udmaCC26XXObject,
        .hwAttrs        = &udmaCC26XXHWAttrs,
    },
};

/*
 *  =============================== ECDH ===============================
 */

#include <ti/drivers/ECDH.h>
#include <ti/drivers/ecdh/ECDHCC26X2.h>

#define CONFIG_ECDH_COUNT 1


ECDHCC26X2_Object ecdhCC26X2Objects[CONFIG_ECDH_COUNT];

/*
 *  ======== ecdhCC26X2HWAttrs ========
 */
const ECDHCC26X2_HWAttrs ecdhCC26X2HWAttrs[CONFIG_ECDH_COUNT] = {
    {
        .intPriority = (~0),
    },
};

const ECDH_Config ECDH_config[CONFIG_ECDH_COUNT] = {
    {   /* CONFIG_ECDH_0 */
        .object         = &ecdhCC26X2Objects[CONFIG_ECDH_0],
        .hwAttrs        = &ecdhCC26X2HWAttrs[CONFIG_ECDH_0]
    },
};

const uint_least8_t CONFIG_ECDH_0_CONST = CONFIG_ECDH_0;
const uint_least8_t ECDH_count = CONFIG_ECDH_COUNT;

/*
 *  =============================== ECDSA ===============================
 */

#include <ti/drivers/ECDSA.h>
#include <ti/drivers/ecdsa/ECDSACC26X2.h>

#define CONFIG_ECDSA_COUNT 1
ECDSACC26X2_Object ecdsaCC26X2Objects[CONFIG_ECDSA_COUNT];

/*
 *  ======== ecdsaCC26X2HWAttrs ========
 */
const ECDSACC26X2_HWAttrs ecdsaCC26X2HWAttrs[CONFIG_ECDSA_COUNT] = {
    {
        .intPriority = (~0),
        .trngIntPriority = (~0),
    },
};

const ECDSA_Config ECDSA_config[CONFIG_ECDSA_COUNT] = {
    {   /* CONFIG_ECDSA_0 */
        .object         = &ecdsaCC26X2Objects[CONFIG_ECDSA_0],
        .hwAttrs        = &ecdsaCC26X2HWAttrs[CONFIG_ECDSA_0]
    },
};

const uint_least8_t CONFIG_ECDSA_0_CONST = CONFIG_ECDSA_0;
const uint_least8_t ECDSA_count = CONFIG_ECDSA_COUNT;

/*
 *  =============================== GPIO ===============================
 */

#include <ti/drivers/GPIO.h>
#include <ti/drivers/gpio/GPIOCC26XX.h>

/* The range of pins available on this device */
const uint_least8_t GPIO_pinLowerBound = 5;
const uint_least8_t GPIO_pinUpperBound = 30;

/* Extern definitions for user callback functions */
extern void fanbee_tachoCB(uint_least8_t index);

/* Called to configure any callbacks defined by sysconfig */
static void configureCallbacks(void) {
    GPIO_setCallback(CONFIG_FAN1_TACHO, fanbee_tachoCB);
}

/*
 *  ======== gpioPinConfigs ========
 *  Array of Pin configurations
 */
GPIO_PinConfig gpioPinConfigs[31] = {
    0, /* Pin is not available on this device */
    0, /* Pin is not available on this device */
    0, /* Pin is not available on this device */
    0, /* Pin is not available on this device */
    0, /* Pin is not available on this device */
    GPIO_CFG_NO_DIR, /* DIO_5 */
    GPIO_CFG_NO_DIR, /* DIO_6 */
    /* Owned by CONFIG_LED_GREEN as LED GPIO */
    GPIO_CFG_OUTPUT_INTERNAL | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW | GPIO_CFG_SLEW_REDUCED, /* CONFIG_GPIO_GLED */
    GPIO_CFG_NO_DIR, /* DIO_8 */
    GPIO_CFG_NO_DIR, /* DIO_9 */
    /* Owned by CONFIG_NVS_SPI_0 as Button GPIO */
    GPIO_CFG_OUTPUT_INTERNAL | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_HIGH, /* CONFIG_GPIO_SPI0_CS0 */
    /* Owned by CONFIG_SPI_0 as POCI */
    GPIO_CFG_INPUT_INTERNAL | GPIO_CFG_IN_INT_NONE | GPIO_CFG_PULL_NONE_INTERNAL, /* CONFIG_GPIO_SPI_0_POCI */
    /* Owned by CONFIG_SPI_0 as PICO */
    GPIO_CFG_OUTPUT_INTERNAL | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW, /* CONFIG_GPIO_SPI_0_PICO */
    /* Owned by CONFIG_SPI_0 as SCLK */
    GPIO_CFG_OUTPUT_INTERNAL | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW, /* CONFIG_GPIO_SPI_0_SCLK */
    /* Owned by CONFIG_GPTIMER_0 as PWM Pin */
    GPIO_CFG_OUTPUT_INTERNAL | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW, /* CONFIG_GPIO_PWM_0 */
    /* Owned by CONFIG_GPTIMER_3 as PWM Pin */
    GPIO_CFG_OUTPUT_INTERNAL | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW, /* CONFIG_GPIO_PWM_3 */
    GPIO_CFG_NO_DIR, /* DIO_16 */
    GPIO_CFG_NO_DIR, /* DIO_17 */
    /* Owned by CONFIG_GPTIMER_2 as PWM Pin */
    GPIO_CFG_OUTPUT_INTERNAL | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW, /* CONFIG_GPIO_PWM_2 */
    GPIO_CFG_OUTPUT_INTERNAL | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW | GPIO_CFG_INVERT_ON, /* CONFIG_DRV_EN */
    GPIO_CFG_NO_DIR, /* DIO_20 */
    GPIO_CFG_NO_DIR, /* DIO_21 */
    GPIO_CFG_INPUT_INTERNAL | GPIO_CFG_IN_INT_FALLING | GPIO_CFG_PULL_NONE_INTERNAL, /* CONFIG_FAN1_TACHO */
    GPIO_CFG_NO_DIR, /* DIO_23 */
    /* Owned by CONFIG_UART as RX */
    GPIO_CFG_INPUT_INTERNAL | GPIO_CFG_IN_INT_NONE | GPIO_CFG_PULL_DOWN_INTERNAL, /* CONFIG_GPIO_UART_RX */
    /* Owned by CONFIG_UART as TX */
    GPIO_CFG_OUTPUT_INTERNAL | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_HIGH, /* CONFIG_GPIO_UART_TX */
    /* Owned by CONFIG_BTN_PAIR as Button GPIO */
    GPIO_CFG_INPUT_INTERNAL | GPIO_CFG_IN_INT_NONE | GPIO_CFG_PULL_NONE_INTERNAL | GPIO_CFG_HYSTERESIS_ON, /* CONFIG_GPIO_BTN_PAIR_INPUT */
    GPIO_CFG_OUTPUT_INTERNAL | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW, /* CONFIG_FAN1_EN */
    /* Owned by /ti/drivers/RF as RF Antenna Pin 0 */
    GPIO_CFG_OUTPUT_INTERNAL | GPIO_CFG_OUT_STR_HIGH | GPIO_CFG_OUT_LOW, /* CONFIG_RF_24GHZ */
    /* Owned by /ti/drivers/RF as RF Antenna Pin 1 */
    GPIO_CFG_OUTPUT_INTERNAL | GPIO_CFG_OUT_STR_HIGH | GPIO_CFG_OUT_LOW, /* CONFIG_RF_HIGH_PA */
    GPIO_CFG_NO_DIR, /* DIO_30 */
};

/*
 *  ======== gpioCallbackFunctions ========
 *  Array of callback function pointers
 *  Change at runtime with GPIO_setCallback()
 */
GPIO_CallbackFxn gpioCallbackFunctions[31];

/*
 *  ======== gpioUserArgs ========
 *  Array of user argument pointers
 *  Change at runtime with GPIO_setUserArg()
 *  Get values with GPIO_getUserArg()
 */
void* gpioUserArgs[31];

const uint_least8_t CONFIG_GPIO_UART_TX_CONST = CONFIG_GPIO_UART_TX;
const uint_least8_t CONFIG_GPIO_UART_RX_CONST = CONFIG_GPIO_UART_RX;
const uint_least8_t CONFIG_FAN1_EN_CONST = CONFIG_FAN1_EN;
const uint_least8_t CONFIG_DRV_EN_CONST = CONFIG_DRV_EN;
const uint_least8_t CONFIG_FAN1_TACHO_CONST = CONFIG_FAN1_TACHO;
const uint_least8_t CONFIG_GPIO_PWM_0_CONST = CONFIG_GPIO_PWM_0;
const uint_least8_t CONFIG_GPIO_PWM_2_CONST = CONFIG_GPIO_PWM_2;
const uint_least8_t CONFIG_GPIO_PWM_3_CONST = CONFIG_GPIO_PWM_3;
const uint_least8_t CONFIG_GPIO_SPI_0_SCLK_CONST = CONFIG_GPIO_SPI_0_SCLK;
const uint_least8_t CONFIG_GPIO_SPI_0_POCI_CONST = CONFIG_GPIO_SPI_0_POCI;
const uint_least8_t CONFIG_GPIO_SPI_0_PICO_CONST = CONFIG_GPIO_SPI_0_PICO;
const uint_least8_t CONFIG_RF_24GHZ_CONST = CONFIG_RF_24GHZ;
const uint_least8_t CONFIG_RF_HIGH_PA_CONST = CONFIG_RF_HIGH_PA;
const uint_least8_t CONFIG_GPIO_GLED_CONST = CONFIG_GPIO_GLED;
const uint_least8_t CONFIG_GPIO_SPI0_CS0_CONST = CONFIG_GPIO_SPI0_CS0;
const uint_least8_t CONFIG_GPIO_BTN_PAIR_INPUT_CONST = CONFIG_GPIO_BTN_PAIR_INPUT;

/*
 *  ======== GPIO_config ========
 */
const GPIO_Config GPIO_config = {
    .configs = (GPIO_PinConfig *)gpioPinConfigs,
    .callbacks = (GPIO_CallbackFxn *)gpioCallbackFunctions,
    .userArgs = gpioUserArgs,
    .intPriority = (~0)
};

/*
 *  =============================== NVS ===============================
 */

#include <ti/drivers/NVS.h>
#include <ti/drivers/nvs/NVSCC26XX.h>

/*
 *  NVSCC26XX Internal NVS flash region definitions
 *
 * Place uninitialized char arrays at addresses
 * corresponding to the 'regionBase' addresses defined in
 * the configured NVS regions. These arrays are used as
 * place holders so that the linker will not place other
 * content there.
 *
 * For GCC targets, the char arrays are each placed into
 * the shared ".nvs" section. The user must add content to
 * their GCC linker command file to place the .nvs section
 * at the lowest 'regionBase' address specified in their NVS
 * regions.
 */

#if defined(__TI_COMPILER_VERSION__) || defined(__clang__)

static char flashBuf0[0x4000] __attribute__ ((retain, noinit, location(0x52000)));

#elif defined(__IAR_SYSTEMS_ICC__)

__no_init static char flashBuf0[0x4000] @ 0x52000;

#elif defined(__GNUC__)

__attribute__ ((section (".nvs")))
static char flashBuf0[0x4000];

#endif

NVSCC26XX_Object nvsCC26XXObjects[1];

static const NVSCC26XX_HWAttrs nvsCC26XXHWAttrs[1] = {
    /* CONFIG_NVSINTERNAL1 */
    {
        .regionBase = (void *) flashBuf0,
        .regionSize = 0x4000
    },
};

#include <ti/drivers/nvs/NVSSPI25X.h>

/*
 *  NVSSPI25X External NVS flash region definitions
 */

/*
 * Provide write verification buffer whose size is
 * the largest specified Verification Buffer Size
 */

static uint8_t verifyBuf[256];

NVSSPI25X_Object nvsSPI25XObjects[1];

static const NVSSPI25X_HWAttrs nvsSPI25XHWAttrs[1] = {
    /* CONFIG_NVSEXTERNAL */
    {
        .regionBaseOffset = 0x0,
        .regionSize = 0x256000,
        .sectorSize = 0x1000,
        .verifyBuf = verifyBuf,
        .verifyBufSize = 256,
        /* NVS opens SPI */
        .spiHandle = NULL,
        /* SPI driver index */
        .spiIndex = CONFIG_SPI_0,
        .spiBitRate = 10000000,
        /* GPIO driver pin index */
        .spiCsnGpioIndex = CONFIG_GPIO_SPI0_CS0,
        .statusPollDelayUs = 100
    },
};

#define CONFIG_NVS_COUNT 2

const NVS_Config NVS_config[CONFIG_NVS_COUNT] = {
    /* CONFIG_NVSINTERNAL1 */
    {
        .fxnTablePtr = &NVSCC26XX_fxnTable,
        .object = &nvsCC26XXObjects[0],
        .hwAttrs = &nvsCC26XXHWAttrs[0],
    },
    /* CONFIG_NVSEXTERNAL */
    {
        .fxnTablePtr = &NVSSPI25X_fxnTable,
        .object = &nvsSPI25XObjects[0],
        .hwAttrs = &nvsSPI25XHWAttrs[0],
    },
};

const uint_least8_t CONFIG_NVSINTERNAL1_CONST = CONFIG_NVSINTERNAL1;
const uint_least8_t CONFIG_NVSEXTERNAL_CONST = CONFIG_NVSEXTERNAL;
const uint_least8_t NVS_count = CONFIG_NVS_COUNT;

/*
 *  =============================== PWM ===============================
 */

#include <ti/drivers/PWM.h>
#include <ti/drivers/pwm/PWMTimerCC26XX.h>

/* include driverlib definitions */
#include <ti/devices/cc13x2_cc26x2/driverlib/ioc.h>
#include <ti/devices/cc13x2_cc26x2/inc/hw_ints.h>
#include <ti/devices/cc13x2_cc26x2/inc/hw_memmap.h>

#define CONFIG_PWM_COUNT 3

/*
 *  ======== pwmCC26XXObjects ========
 */
PWMTimerCC26XX_Object pwmTimerCC26XXObjects[CONFIG_PWM_COUNT];

/*
 *  ======== pwmCC26XXHWAttrs ========
 */
const PWMTimerCC26XX_HwAttrs pwmTimerCC26XXHWAttrs[CONFIG_PWM_COUNT] = {
    /* CONFIG_PWM_FAN1 */
    {
        .pwmPin = CONFIG_GPIO_PWM_0,
        .gpTimerUnit = CONFIG_GPTIMER_0
    },
    /* CONFIG_PWM_SRV1 */
    {
        .pwmPin = CONFIG_GPIO_PWM_2,
        .gpTimerUnit = CONFIG_GPTIMER_2
    },
    /* CONFIG_PWM_SRV2 */
    {
        .pwmPin = CONFIG_GPIO_PWM_3,
        .gpTimerUnit = CONFIG_GPTIMER_3
    },
};

/*
 *  ======== PWM_config ========
 */
const PWM_Config PWM_config[CONFIG_PWM_COUNT] = {
    /* CONFIG_PWM_FAN1 */
    {
        .fxnTablePtr = &PWMTimerCC26XX_fxnTable,
        .object = &pwmTimerCC26XXObjects[CONFIG_PWM_FAN1],
        .hwAttrs = &pwmTimerCC26XXHWAttrs[CONFIG_PWM_FAN1]
    },
    /* CONFIG_PWM_SRV1 */
    {
        .fxnTablePtr = &PWMTimerCC26XX_fxnTable,
        .object = &pwmTimerCC26XXObjects[CONFIG_PWM_SRV1],
        .hwAttrs = &pwmTimerCC26XXHWAttrs[CONFIG_PWM_SRV1]
    },
    /* CONFIG_PWM_SRV2 */
    {
        .fxnTablePtr = &PWMTimerCC26XX_fxnTable,
        .object = &pwmTimerCC26XXObjects[CONFIG_PWM_SRV2],
        .hwAttrs = &pwmTimerCC26XXHWAttrs[CONFIG_PWM_SRV2]
    },
};

const uint_least8_t CONFIG_PWM_FAN1_CONST = CONFIG_PWM_FAN1;
const uint_least8_t CONFIG_PWM_SRV1_CONST = CONFIG_PWM_SRV1;
const uint_least8_t CONFIG_PWM_SRV2_CONST = CONFIG_PWM_SRV2;
const uint_least8_t PWM_count = CONFIG_PWM_COUNT;

/*
 *  =============================== Power ===============================
 */
#include <ti/drivers/Power.h>
#include <ti/drivers/power/PowerCC26X2.h>
#include "ti_drivers_config.h"

extern void PowerCC26XX_standbyPolicy(void);
extern bool PowerCC26XX_calibrate(unsigned int);

const PowerCC26X2_Config PowerCC26X2_config = {
    .enablePolicy             = true,
    .policyInitFxn            = NULL,
    .policyFxn                = PowerCC26XX_standbyPolicy,
    .calibrateFxn             = PowerCC26XX_calibrate,
    .calibrateRCOSC_LF        = true,
    .calibrateRCOSC_HF        = true,
    .enableTCXOFxn            = NULL
};



/*
 *  =============================== RF Driver ===============================
 */
#include <ti/drivers/GPIO.h>
#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(driverlib/ioc.h)
#include <ti/drivers/rf/RF.h>

/*
 * RF driver callback function, called by the driver on global driver events.
 */
static void RF_globalCallbackFunction (RF_Handle client, RF_GlobalEvent events, void* arg);

/*
 * Callback function to handle custom / application specific behavior
 */
extern void __attribute__((weak)) rfDriverCallback (RF_Handle client, RF_GlobalEvent events, void *arg);

/*
 * Callback function to handle antenna switching
 */
extern void __attribute__((weak)) rfDriverCallbackAntennaSwitching (RF_Handle client, RF_GlobalEvent events, void *arg);

/*
 * Platform-specific driver configuration
 */
const RFCC26XX_HWAttrsV2 RFCC26XX_hwAttrs = {
    .hwiPriority        = (~0),
    .swiPriority        = (uint8_t)0,
    .xoscHfAlwaysNeeded = true,
    .globalCallback     = &RF_globalCallbackFunction,
    .globalEventMask    = RF_GlobalEventInit | RF_GlobalEventRadioPowerDown | RF_GlobalEventRadioSetup
};

/*
 *  ======== RF_globalCallbackFunction ========
 *  This function is called by the driver on global driver events.
 *  It will call specific callback functions to further handle the triggering events.
 */
static void RF_globalCallbackFunction(RF_Handle client, RF_GlobalEvent events, void *arg)
{
    rfDriverCallback(client, events, arg);
    rfDriverCallbackAntennaSwitching(client, events, arg);
}

/*
 *  ======== rfDriverCallback ========
 *  Handle events triggered by the RF driver for custom / application specific behavior.
 */
void __attribute__((weak)) rfDriverCallback(RF_Handle client, RF_GlobalEvent events, void *arg)
{
    /* ======== PLEASE READ THIS ========
    *
    * This function is declared weak for the application to override it.
    * A new definition of 'rfDriverCallback' is required if you want to
    * handle the events listed in '.globalEventMask'.
    *
    * Please copy this function definition to create your own, but make
    * sure to remove '__attribute__((weak))' for your definition.
    *
    * According to '.globalEventMask', this function will be triggered by:
    *   - RF_GlobalEventInit
    *   - RF_GlobalEventRadioPowerDown
    *   - RF_GlobalEventRadioSetup
    *
    * An example of how to handle these events would be:
    *
    *   --- Code snippet begin ---
    *
    *   if(events & RF_GlobalEventInit) {
    *       // Perform action for this event
    *   }
    *   else if (events & RF_GlobalEventRadioPowerDown) {
    *       // Perform action for this event
    *   }
    *   else if (events & RF_GlobalEventRadioSetup) {
    *       // Perform action for this event
    *   }
    *
    *   --- Code snippet end ---
    */
}



/*
 * ======== Antenna switching ========
 */
/*
 * ======== rfDriverCallbackAntennaSwitching ========
 * Function to handle antenna switching.
 */
void __attribute__((weak)) rfDriverCallbackAntennaSwitching(RF_Handle client, RF_GlobalEvent events, void *arg)
{
    /* ======== PLEASE READ THIS ========
    *
    * This function is declared weak for the application to override it,
    * and the undefined function call below is intended to catch the
    * developer's attention at link time.
    * A new definition of 'rfDriverCallbackAntennaSwitching' is required.
    *
    * Please copy this function definition to create your own, but make
    * sure to remove '__attribute__((weak))' for your definition and
    * remove the below function declaration and function call.
    *
    * To handle the events listed in '.globalEventMask', please see the
    * help text provided in 'rfDriverCallback' above.
    *
    * For an example on how to interact with the selected antenna pins,
    * please see the code snippet below:
    *
    *   --- Code snippet begin ---
    *
    * // > This assumes antenna switch pins have been added to GPIO via
    * // > sysconfig with the following properties:
    * // >     mode: Output
    * // >     initialOutputState: Low
    * // >     outputStrength: High
    *
    * // > Set pin output value manually
    * GPIO_write(CONFIG_RF_24GHZ, 0); // Low
    * GPIO_write(CONFIG_RF_24GHZ, 1); // High
    *
    * // > Mux pin to be driven/controlled by the RF Core
    * // > (RFC GPIO0 is here only used as an example)
    * GPIO_setMux(CONFIG_RF_24GHZ, IOC_PORT_RFC_GPO0);
    *
    * // > Mux pin to be controlled manually (i.e. release RF Core control)
    * GPIO_setMux(CONFIG_RF_24GHZ, IOC_PORT_GPIO);
    *
    *   --- Code snippet end ---
    */
    extern void you_must_implement_rfDriverCallbackAntennaSwitching_see_generated_ti_drivers_config_c_in_debug_folder_or_sysconfig_preview(void);
    you_must_implement_rfDriverCallbackAntennaSwitching_see_generated_ti_drivers_config_c_in_debug_folder_or_sysconfig_preview();
}

/*
 *  =============================== SHA2 ===============================
 */

#include <ti/drivers/SHA2.h>
#include <ti/drivers/sha2/SHA2CC26X2.h>

#define CONFIG_SHA2_COUNT 1


SHA2CC26X2_Object sha2CC26X2Objects[CONFIG_SHA2_COUNT];

/*
 *  ======== sha2CC26X2HWAttrs ========
 */
const SHA2CC26X2_HWAttrs sha2CC26X2HWAttrs[CONFIG_SHA2_COUNT] = {
    {
        .intPriority = (~0),
    },
};

const SHA2_Config SHA2_config[CONFIG_SHA2_COUNT] = {
    {   /* CONFIG_SHA2_0 */
        .object         = &sha2CC26X2Objects[CONFIG_SHA2_0],
        .hwAttrs        = &sha2CC26X2HWAttrs[CONFIG_SHA2_0]
    },
};

const uint_least8_t CONFIG_SHA2_0_CONST = CONFIG_SHA2_0;
const uint_least8_t SHA2_count = CONFIG_SHA2_COUNT;

/*
 *  =============================== SPI DMA ===============================
 */
#include <ti/drivers/SPI.h>
#include <ti/drivers/spi/SPICC26X2DMA.h>
#include <ti/drivers/dma/UDMACC26XX.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(driverlib/ioc.h)

#define CONFIG_SPI_COUNT 1

/*
 *  ======== spiCC26X2DMAObjects ========
 */
SPICC26X2DMA_Object spiCC26X2DMAObjects[CONFIG_SPI_COUNT];

/*
 * ======== spiCC26X2DMA uDMA Table Entries  ========
 */
ALLOCATE_CONTROL_TABLE_ENTRY(dmaSpi0TxControlTableEntry, UDMA_CHAN_SSI0_TX);
ALLOCATE_CONTROL_TABLE_ENTRY(dmaSpi0RxControlTableEntry, UDMA_CHAN_SSI0_RX);
ALLOCATE_CONTROL_TABLE_ENTRY(dmaSpi0TxAltControlTableEntry, (UDMA_CHAN_SSI0_TX | UDMA_ALT_SELECT));
ALLOCATE_CONTROL_TABLE_ENTRY(dmaSpi0RxAltControlTableEntry, (UDMA_CHAN_SSI0_RX | UDMA_ALT_SELECT));


/*
 *  ======== spiCC26X2DMAHWAttrs ========
 */
const SPICC26X2DMA_HWAttrs spiCC26X2DMAHWAttrs[CONFIG_SPI_COUNT] = {
    /* CONFIG_SPI_0 */
    {
        .baseAddr = SSI0_BASE,
        .intNum = INT_SSI0_COMB,
        .intPriority = (~0),
        .swiPriority = 0,
        .powerMngrId = PowerCC26XX_PERIPH_SSI0,
        .defaultTxBufValue = ~0,
        .rxChannelBitMask = 1<<UDMA_CHAN_SSI0_RX,
        .txChannelBitMask = 1<<UDMA_CHAN_SSI0_TX,
        .dmaTxTableEntryPri = &dmaSpi0TxControlTableEntry,
        .dmaRxTableEntryPri = &dmaSpi0RxControlTableEntry,
        .dmaTxTableEntryAlt = &dmaSpi0TxAltControlTableEntry,
        .dmaRxTableEntryAlt = &dmaSpi0RxAltControlTableEntry,
        .minDmaTransferSize = 10,
        .txPinMux    = IOC_PORT_MCU_SSI0_TX,
        .rxPinMux    = IOC_PORT_MCU_SSI0_RX,
        .clkPinMux   = IOC_PORT_MCU_SSI0_CLK,
        .csnPinMux   = IOC_PORT_MCU_SSI0_FSS,
        .picoPin = CONFIG_GPIO_SPI_0_PICO,
        .pociPin = CONFIG_GPIO_SPI_0_POCI,
        .clkPin  = CONFIG_GPIO_SPI_0_SCLK,
        .csnPin  = GPIO_INVALID_INDEX
    },
};

/*
 *  ======== SPI_config ========
 */
const SPI_Config SPI_config[CONFIG_SPI_COUNT] = {
    /* CONFIG_SPI_0 */
    {
        .fxnTablePtr = &SPICC26X2DMA_fxnTable,
        .object = &spiCC26X2DMAObjects[CONFIG_SPI_0],
        .hwAttrs = &spiCC26X2DMAHWAttrs[CONFIG_SPI_0]
    },
};

const uint_least8_t CONFIG_SPI_0_CONST = CONFIG_SPI_0;
const uint_least8_t SPI_count = CONFIG_SPI_COUNT;

/*
 *  =============================== TRNG ===============================
 */

#include <ti/drivers/TRNG.h>
#include <ti/drivers/trng/TRNGCC26XX.h>

#define CONFIG_TRNG_COUNT 1


TRNGCC26XX_Object trngCC26XXObjects[CONFIG_TRNG_COUNT];

/*
 *  ======== trngCC26XXHWAttrs ========
 */
static const TRNGCC26XX_HWAttrs trngCC26XXHWAttrs[CONFIG_TRNG_COUNT] = {
    {
        .intPriority = (~0),
        .swiPriority = 0,
        .samplesPerCycle = 240000
    },
};

const TRNG_Config TRNG_config[CONFIG_TRNG_COUNT] = {
    {   /* CONFIG_TRNG_0 */
        .object         = &trngCC26XXObjects[CONFIG_TRNG_0],
        .hwAttrs        = &trngCC26XXHWAttrs[CONFIG_TRNG_0]
    },
};

const uint_least8_t CONFIG_TRNG_0_CONST = CONFIG_TRNG_0;
const uint_least8_t TRNG_count = CONFIG_TRNG_COUNT;

/*
 *  =============================== UART2 ===============================
 */

#include <ti/drivers/UART2.h>
#include <ti/drivers/uart2/UART2CC26X2.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/Power.h>
#include <ti/drivers/dma/UDMACC26XX.h>
#include <ti/drivers/power/PowerCC26X2.h>
#include <ti/devices/cc13x2_cc26x2/driverlib/ioc.h>
#include <ti/devices/cc13x2_cc26x2/inc/hw_memmap.h>
#include <ti/devices/cc13x2_cc26x2/inc/hw_ints.h>

#define CONFIG_UART2_COUNT 1

UART2CC26X2_Object uart2CC26X2Objects[CONFIG_UART2_COUNT];

static unsigned char uart2RxRingBuffer0[32];
/* TX ring buffer allocated to be used for nonblocking mode */
static unsigned char uart2TxRingBuffer0[32];

ALLOCATE_CONTROL_TABLE_ENTRY(dmaUart1RxControlTableEntry, UDMA_CHAN_UART1_RX);
ALLOCATE_CONTROL_TABLE_ENTRY(dmaUart1TxControlTableEntry, UDMA_CHAN_UART1_TX);

static const UART2CC26X2_HWAttrs uart2CC26X2HWAttrs[CONFIG_UART2_COUNT] = {
  {
    .baseAddr           = UART1_BASE,
    .intNum             = INT_UART1_COMB,
    .intPriority        = (~0),
    .rxPin              = CONFIG_GPIO_UART_RX,
    .txPin              = CONFIG_GPIO_UART_TX,
    .ctsPin             = GPIO_INVALID_INDEX,
    .rtsPin             = GPIO_INVALID_INDEX,
    .flowControl        = UART2_FLOWCTRL_NONE,
    .powerId            = PowerCC26XX_PERIPH_UART1,
    .rxBufPtr           = uart2RxRingBuffer0,
    .rxBufSize          = sizeof(uart2RxRingBuffer0),
    .txBufPtr           = uart2TxRingBuffer0,
    .txBufSize          = sizeof(uart2TxRingBuffer0),
    .txPinMux           = IOC_PORT_MCU_UART1_TX,
    .rxPinMux           = IOC_PORT_MCU_UART1_RX,
    .ctsPinMux          = IOC_PORT_MCU_UART1_CTS,
    .rtsPinMux          = IOC_PORT_MCU_UART1_RTS,
    .dmaTxTableEntryPri = &dmaUart1TxControlTableEntry,
    .dmaRxTableEntryPri = &dmaUart1RxControlTableEntry,
    .rxChannelMask      = 1 << UDMA_CHAN_UART1_RX,
    .txChannelMask      = 1 << UDMA_CHAN_UART1_TX,
    .txIntFifoThr       = UART2CC26X2_FIFO_THRESHOLD_1_8,
    .rxIntFifoThr       = UART2CC26X2_FIFO_THRESHOLD_4_8
  },
};

const UART2_Config UART2_config[CONFIG_UART2_COUNT] = {
    {   /* CONFIG_UART */
        .object      = &uart2CC26X2Objects[CONFIG_UART],
        .hwAttrs     = &uart2CC26X2HWAttrs[CONFIG_UART]
    },
};

const uint_least8_t CONFIG_UART_CONST = CONFIG_UART;
const uint_least8_t UART2_count = CONFIG_UART2_COUNT;


/*
 *  =============================== Button ===============================
 */
#include <ti/drivers/apps/Button.h>

#define CONFIG_BUTTON_COUNT 1
Button_Object ButtonObjects[CONFIG_BUTTON_COUNT];

static const Button_HWAttrs ButtonHWAttrs[CONFIG_BUTTON_COUNT] = {
    /* CONFIG_BTN_PAIR */
    {
        .gpioIndex = CONFIG_GPIO_BTN_PAIR_INPUT,
        .pullMode = Button_PULL_UP,
        .internalPullEnabled = 0,
    },
};

const Button_Config Button_config[CONFIG_BUTTON_COUNT] = {
    /* CONFIG_BTN_PAIR */
    {
        .object = &ButtonObjects[CONFIG_BTN_PAIR],
        .hwAttrs = &ButtonHWAttrs[CONFIG_BTN_PAIR]
    },
};

const uint_least8_t CONFIG_BTN_PAIR_CONST = CONFIG_BTN_PAIR;
const uint_least8_t Button_count = CONFIG_BUTTON_COUNT;

/*
 *  =============================== LED ===============================
 */
#include <ti/drivers/apps/LED.h>

#define CONFIG_LED_COUNT 1
LED_Object LEDObjects[CONFIG_LED_COUNT];

static const LED_HWAttrs LEDHWAttrs[CONFIG_LED_COUNT] = {
    /* CONFIG_LED_GREEN */
    {
        .type = LED_GPIO_CONTROLLED,
        .index = CONFIG_GPIO_GLED,
    },
};

const LED_Config LED_config[CONFIG_LED_COUNT] = {
    /* CONFIG_LED_GREEN */
    {
        .object = &LEDObjects[CONFIG_LED_GREEN],
        .hwAttrs = &LEDHWAttrs[CONFIG_LED_GREEN]
    },
};

const uint_least8_t CONFIG_LED_GREEN_CONST = CONFIG_LED_GREEN;
const uint_least8_t LED_count = CONFIG_LED_COUNT;

/*
 *  =============================== GPTimer ===============================
 */

#include <ti/drivers/timer/GPTimerCC26XX.h>
#include <ti/drivers/power/PowerCC26XX.h>
#include <ti/devices/cc13x2_cc26x2/inc/hw_memmap.h>
#include <ti/devices/cc13x2_cc26x2/inc/hw_ints.h>

#define CONFIG_GPTIMER_COUNT 3

/*
 *  ======== gptimerCC26XXObjects ========
 */
GPTimerCC26XX_Object gptimerCC26XXObjects[CONFIG_GPTIMER_COUNT];

/*
 *  ======== gptimerCC26XXHWAttrs ========
 */
const GPTimerCC26XX_HWAttrs gptimerCC26XXHWAttrs[CONFIG_GPTIMER_COUNT] = {
    /* CONFIG_GPTIMER_0, used by CONFIG_PWM_FAN1 */
    {
        .baseAddr = GPT3_BASE,
        .intNum      = INT_GPT3A,
        .intPriority = (~0),
        .powerMngrId = PowerCC26XX_PERIPH_GPT3,
        .pinMux      = GPT_PIN_3A
    },
    /* CONFIG_GPTIMER_2, used by CONFIG_PWM_SRV1 */
    {
        .baseAddr = GPT2_BASE,
        .intNum      = INT_GPT2A,
        .intPriority = (~0),
        .powerMngrId = PowerCC26XX_PERIPH_GPT2,
        .pinMux      = GPT_PIN_2A
    },
    /* CONFIG_GPTIMER_3, used by CONFIG_PWM_SRV2 */
    {
        .baseAddr = GPT2_BASE,
        .intNum      = INT_GPT2B,
        .intPriority = (~0),
        .powerMngrId = PowerCC26XX_PERIPH_GPT2,
        .pinMux      = GPT_PIN_2B
    },
};

/*
 *  ======== GPTimer_config ========
 */
const GPTimerCC26XX_Config GPTimerCC26XX_config[CONFIG_GPTIMER_COUNT] = {
    /* CONFIG_GPTIMER_0 */
    {
        .object    = &gptimerCC26XXObjects[CONFIG_GPTIMER_0],
        .hwAttrs   = &gptimerCC26XXHWAttrs[CONFIG_GPTIMER_0],
        .timerPart = GPT_A
    },
    /* CONFIG_GPTIMER_2 */
    {
        .object    = &gptimerCC26XXObjects[CONFIG_GPTIMER_2],
        .hwAttrs   = &gptimerCC26XXHWAttrs[CONFIG_GPTIMER_2],
        .timerPart = GPT_A
    },
    /* CONFIG_GPTIMER_3 */
    {
        .object    = &gptimerCC26XXObjects[CONFIG_GPTIMER_3],
        .hwAttrs   = &gptimerCC26XXHWAttrs[CONFIG_GPTIMER_3],
        .timerPart = GPT_B
    },
};

const uint_least8_t CONFIG_GPTIMER_0_CONST = CONFIG_GPTIMER_0;
const uint_least8_t CONFIG_GPTIMER_2_CONST = CONFIG_GPTIMER_2;
const uint_least8_t CONFIG_GPTIMER_3_CONST = CONFIG_GPTIMER_3;
const uint_least8_t GPTimer_count = CONFIG_GPTIMER_COUNT;

#include <ti/drivers/Board.h>

/*
 *  ======== Board_initHook ========
 *  Perform any board-specific initialization needed at startup.  This
 *  function is declared weak to allow applications to override it if needed.
 */
void __attribute__((weak)) Board_initHook(void)
{
}

/*
 *  ======== Board_init ========
 *  Perform any initialization needed before using any board APIs
 */
void Board_init(void)
{
    /* ==== /ti/drivers/Power initialization ==== */
    Power_init();

    /* ==== /ti/devices/CCFG initialization ==== */

    /* ==== /ti/drivers/GPIO initialization ==== */
    /* Setup GPIO module and default-initialise pins */
    GPIO_init();
    configureCallbacks();

    /* ==== /ti/drivers/RF initialization ==== */

    Board_initHook();
}

