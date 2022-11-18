#ifndef NTC_COMMON_H
#define NTC_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
// #include "NTC_cfg.h"

#ifndef MCU_TYPE
#define MCU_TYPE == 1 /* TRAVEOII */
#endif

// #if (MCU_TYPE == MCU_MB9BF560)
// #include "base_types.h"
// #elif (MCU_TYPE == MCU_TRAVEOII)  
// #include "cy_project.h"
// #endif

typedef enum {
    UNKNOWN_NTC_MODEL,     
    NTC_VISHAY_10K,             /* Vishay Dale 10K con partitore 4K7 1%-390K */
    NTC_TDK_10K,                /* TDK 10K con partitore 10K 1%-1M */
    NTC_VSH_4M1003B3C4,         /* Vishay Dale 4M1003-B3(curve 4) con partitore 4K7 1%-390K */
    NTC_VSH_1M1002B3C1,         /* Vishay Dale 1M1002-B3(curve 1) con partitore 3K3 1%-390K */
    NTC_EUROSWITCH100K,         /* Euroswitch 100 K con partitore 3K3 1%-390K */
    NTC_TDK_B57500M             /* TDK B57500M con partitore 3K3 1%-390K */ 
} NTC_sensor_model;

/* List of all NTC errors */
typedef enum 
{
    NO_NTC_IMPLEMENTATION,
    EMPTY_NTC_TABLE,
    NTC_SHORT_CIRCUIT,
    NTC_OPEN_CIRCUIT, 
    NTC_NO_ADC_RES_SET
} NTC_error_t;

/* List of error messages according to NTC_error_t list */
#ifdef DEBUG_MESSAGES
char *NTC_error_t_messages[] = 
{
    "NTC sensor is not implemented!",
    "Empty NTC curve",
    "Short circuit",
    "Open circuit" 
    "Wrong ADC resolution or steps"
}

#define print_error_message(err_code) printf("[NTC]: %s\n", NTC_error_t_messages[err_code])
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* NTC_COMMON_H */

/***********************************************************************************************************************
 * END OF FILE
 **********************************************************************************************************************/
