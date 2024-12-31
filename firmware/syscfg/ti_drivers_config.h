/*
 *  ======== ti_drivers_config.h ========
 *  Configured TI-Drivers module declarations
 *
 *  The macros defines herein are intended for use by applications which
 *  directly include this header. These macros should NOT be hard coded or
 *  copied into library source code.
 *
 *  Symbols declared as const are intended for use with libraries.
 *  Library source code must extern the correct symbol--which is resolved
 *  when the application is linked.
 *
 *  DO NOT EDIT - This file is generated for the CC1352P1F3RGZ
 *  by the SysConfig tool.
 */
#ifndef ti_drivers_config_h
#define ti_drivers_config_h

#define CONFIG_SYSCONFIG_PREVIEW

#define CONFIG_CC1352P1F3RGZ
#ifndef DeviceFamily_CC13X2
#define DeviceFamily_CC13X2
#endif

#include <ti/devices/DeviceFamily.h>

#include <stdint.h>

/* support C++ sources */
#ifdef __cplusplus
extern "C" {
#endif


/*
 *  ======== CCFG ========
 */


/*
 *  ======== AESCBC ========
 */

extern const uint_least8_t                  CONFIG_AESCBC_0_CONST;
#define CONFIG_AESCBC_0                     0
#define CONFIG_TI_DRIVERS_AESCBC_COUNT      1


/*
 *  ======== AESCCM ========
 */

extern const uint_least8_t                  CONFIG_AESCCM_0_CONST;
#define CONFIG_AESCCM_0                     0
#define CONFIG_TI_DRIVERS_AESCCM_COUNT      1


/*
 *  ======== AESECB ========
 */

extern const uint_least8_t                  CONFIG_AESECB_0_CONST;
#define CONFIG_AESECB_0                     0
#define CONFIG_TI_DRIVERS_AESECB_COUNT      1


/*
 *  ======== ECDH ========
 */

extern const uint_least8_t              CONFIG_ECDH_0_CONST;
#define CONFIG_ECDH_0                   0
#define CONFIG_TI_DRIVERS_ECDH_COUNT    1


/*
 *  ======== ECDSA ========
 */

extern const uint_least8_t                  CONFIG_ECDSA_0_CONST;
#define CONFIG_ECDSA_0                      0
#define CONFIG_TI_DRIVERS_ECDSA_COUNT       1


/*
 *  ======== GPIO ========
 */
/* Owned by CONFIG_UART as  */
extern const uint_least8_t CONFIG_GPIO_UART_TX_CONST;
#define CONFIG_GPIO_UART_TX 25

/* Owned by CONFIG_UART as  */
extern const uint_least8_t CONFIG_GPIO_UART_RX_CONST;
#define CONFIG_GPIO_UART_RX 24

extern const uint_least8_t CONFIG_FAN1_EN_CONST;
#define CONFIG_FAN1_EN 27

extern const uint_least8_t CONFIG_DRV_EN_CONST;
#define CONFIG_DRV_EN 19

extern const uint_least8_t CONFIG_FAN1_TACHO_CONST;
#define CONFIG_FAN1_TACHO 22

/* Owned by CONFIG_GPTIMER_0 as  */
extern const uint_least8_t CONFIG_GPIO_PWM_0_CONST;
#define CONFIG_GPIO_PWM_0 14

/* Owned by CONFIG_GPTIMER_2 as  */
extern const uint_least8_t CONFIG_GPIO_PWM_2_CONST;
#define CONFIG_GPIO_PWM_2 18

/* Owned by CONFIG_GPTIMER_3 as  */
extern const uint_least8_t CONFIG_GPIO_PWM_3_CONST;
#define CONFIG_GPIO_PWM_3 15

/* Owned by CONFIG_SPI_0 as  */
extern const uint_least8_t CONFIG_GPIO_SPI_0_SCLK_CONST;
#define CONFIG_GPIO_SPI_0_SCLK 13

/* Owned by CONFIG_SPI_0 as  */
extern const uint_least8_t CONFIG_GPIO_SPI_0_POCI_CONST;
#define CONFIG_GPIO_SPI_0_POCI 11

/* Owned by CONFIG_SPI_0 as  */
extern const uint_least8_t CONFIG_GPIO_SPI_0_PICO_CONST;
#define CONFIG_GPIO_SPI_0_PICO 12

/* Owned by /ti/drivers/RF as  */
extern const uint_least8_t CONFIG_RF_24GHZ_CONST;
#define CONFIG_RF_24GHZ 28

/* Owned by /ti/drivers/RF as  */
extern const uint_least8_t CONFIG_RF_HIGH_PA_CONST;
#define CONFIG_RF_HIGH_PA 29

/* Owned by CONFIG_LED_GREEN as  */
extern const uint_least8_t CONFIG_GPIO_GLED_CONST;
#define CONFIG_GPIO_GLED 7

/* Owned by CONFIG_NVS_SPI_0 as  */
extern const uint_least8_t CONFIG_GPIO_SPI0_CS0_CONST;
#define CONFIG_GPIO_SPI0_CS0 10

/* Owned by CONFIG_BTN_PAIR as  */
extern const uint_least8_t CONFIG_GPIO_BTN_PAIR_INPUT_CONST;
#define CONFIG_GPIO_BTN_PAIR_INPUT 26

/* The range of pins available on this device */
extern const uint_least8_t GPIO_pinLowerBound;
extern const uint_least8_t GPIO_pinUpperBound;

/* LEDs are active high */
#define CONFIG_GPIO_LED_ON  (1)
#define CONFIG_GPIO_LED_OFF (0)

#define CONFIG_LED_ON  (CONFIG_GPIO_LED_ON)
#define CONFIG_LED_OFF (CONFIG_GPIO_LED_OFF)


/*
 *  ======== NVS ========
 */

extern const uint_least8_t              CONFIG_NVSINTERNAL1_CONST;
#define CONFIG_NVSINTERNAL1             0
/*
 *  PICO: DIO12
 *  POCI: DIO11
 *  SCLK: DIO13
 *  CSN: undefined
 */
extern const uint_least8_t              CONFIG_NVSEXTERNAL_CONST;
#define CONFIG_NVSEXTERNAL              1
#define CONFIG_TI_DRIVERS_NVS_COUNT     2


/*
 *  ======== PWM ========
 */

/* DIO14 */
extern const uint_least8_t              CONFIG_PWM_FAN1_CONST;
#define CONFIG_PWM_FAN1                 0
/* DIO18 */
extern const uint_least8_t              CONFIG_PWM_SRV1_CONST;
#define CONFIG_PWM_SRV1                 1
/* DIO15 */
extern const uint_least8_t              CONFIG_PWM_SRV2_CONST;
#define CONFIG_PWM_SRV2                 2
#define CONFIG_TI_DRIVERS_PWM_COUNT     3




/*
 *  ======== SHA2 ========
 */

extern const uint_least8_t              CONFIG_SHA2_0_CONST;
#define CONFIG_SHA2_0                   0
#define CONFIG_TI_DRIVERS_SHA2_COUNT    1


/*
 *  ======== SPI ========
 */

/*
 *  PICO: DIO12
 *  POCI: DIO11
 *  SCLK: DIO13
 */
extern const uint_least8_t              CONFIG_SPI_0_CONST;
#define CONFIG_SPI_0                    0
#define CONFIG_TI_DRIVERS_SPI_COUNT     1


/*
 *  ======== TRNG ========
 */

extern const uint_least8_t              CONFIG_TRNG_0_CONST;
#define CONFIG_TRNG_0                   0
#define CONFIG_TI_DRIVERS_TRNG_COUNT    1


/*
 *  ======== UART2 ========
 */

/*
 *  TX: DIO25
 *  RX: DIO24
 */
extern const uint_least8_t                  CONFIG_UART_CONST;
#define CONFIG_UART                         0
#define CONFIG_TI_DRIVERS_UART2_COUNT       1


/*
 *  ======== Button ========
 */

extern const uint_least8_t                  CONFIG_BTN_PAIR_CONST;
#define CONFIG_BTN_PAIR                     0
#define CONFIG_TI_DRIVERS_BUTTON_COUNT      1


/*
 *  ======== LED ========
 */

extern const uint_least8_t              CONFIG_LED_GREEN_CONST;
#define CONFIG_LED_GREEN                0
#define CONFIG_TI_DRIVERS_LED_COUNT     1


/*
 *  ======== GPTimer ========
 */

extern const uint_least8_t                  CONFIG_GPTIMER_0_CONST;
#define CONFIG_GPTIMER_0                    0
extern const uint_least8_t                  CONFIG_GPTIMER_2_CONST;
#define CONFIG_GPTIMER_2                    1
extern const uint_least8_t                  CONFIG_GPTIMER_3_CONST;
#define CONFIG_GPTIMER_3                    2
#define CONFIG_TI_DRIVERS_GPTIMER_COUNT     3


/*
 *  ======== Board_init ========
 *  Perform all required TI-Drivers initialization
 *
 *  This function should be called once at a point before any use of
 *  TI-Drivers.
 */
extern void Board_init(void);

/*
 *  ======== Board_initGeneral ========
 *  (deprecated)
 *
 *  Board_initGeneral() is defined purely for backward compatibility.
 *
 *  All new code should use Board_init() to do any required TI-Drivers
 *  initialization _and_ use <Driver>_init() for only where specific drivers
 *  are explicitly referenced by the application.  <Driver>_init() functions
 *  are idempotent.
 */
#define Board_initGeneral Board_init

#ifdef __cplusplus
}
#endif

#endif /* include guard */
