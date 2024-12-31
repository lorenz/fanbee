#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "nvintf.h"
#include "zcl.h"
#include "zcl_config.h"

#define FANBEE_NV_CURRENT_LEVEL 0x0010
#define FANBEE_NV_ONOFF 0x0011
#define FANBEE_NV_SERVO_MIN_POS 0x0012
#define FANBEE_NV_SERVO_MAX_POS 0x0013
#define FANBEE_NV_FAN_MIN_PWM 0x0014

#define FANBEE_TACHO_EVT 0x0100
#define FANBEE_RESET_EVT 0x0200
#define FANBEE_PAIR_EVT 0x0400

#define FANBEE_GP_DATA_SEND_EVT 0x1000
#define FANBEE_GP_EXPIRE_DUPLICATE_EVT 0x2000
#define FANBEE_GP_TEMP_MASTER_EVT 0x4000

#define FANBEE_CONFIG_CLUSTER 0xff01
#define ATTRID_SERVO_MIN_POS 0x0
#define ATTRID_SERVO_MAX_POS 0x1
#define ATTRID_FAN_MIN_PWM 0x2

#ifdef __cplusplus
}
#endif
