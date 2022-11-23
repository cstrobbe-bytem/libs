#ifndef COMMON_H
#define COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

#define MCU_MB9BF560        0
#ifndef CYT2B97CAE
#define MCU_CYT2B97CAE      1
#else
#define MCU_CYT2B97CAE      CYT2B97CAE
#endif
#define MCU_STM32H750xx     3

#include <stdint.h>

uint32_t scale_color(uint32_t color_, float scaler_);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* COMMON_H */