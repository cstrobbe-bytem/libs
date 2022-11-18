#ifndef NTC_CFG_H
#define NTC_CFG_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef BOARD_CFG_FILE /* ONLY For debug purposes */
#include "../Utils/common.h"
#define MCU_TYPE            MCU_TRAVEOII
#else
#include "board_cfg.h" /* Include board description together with NTC sensors available */
#endif /* BOARD_CFG_FILE */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* NTC_CFG_H */