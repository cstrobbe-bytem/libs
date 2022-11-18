/**
* \file test_cm4.cpp
*
* \brief
* Main file for CM4
*
*******************************************************************************/

//#include "cy_project.h"
//#include "cy_device_headers.h"

#include "../models/Vishay10K.hpp"
#include "../models/TDK10K.hpp"

#define USER_LED_PORT           GPIO_PRT20
#define USER_LED_PIN            1
#define USER_LED_PIN_MUX        P20_1_GPIO

#define NUM_OF_TESTS     50
#define TEST_SUCCESSFUL  1
#define TEST_FAILED      0

//cy_stc_gpio_pin_config_t user_led_port_pin_cfg =
//{
//    .outVal    = 0x00,
//    .driveMode = CY_GPIO_DM_STRONG_IN_OFF,
//    .hsiom     = USER_LED_PIN_MUX,
//    .intEdge   = 0,
//    .intMask   = 0,
//    .vtrip     = 0,
//    .slewRate  = 0,
//    .driveSel  = 0,
//    .vregEn    = 0,
//    .ibufMode  = 0,
//    .vtripSel  = 0,
//    .vrefSel   = 0,
//    .vohSel    = 0,
//};

int main(void)
{
//    __enable_irq();
//	
//    SystemInit();
//
//    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
//    Cy_GPIO_Pin_Init(USER_LED_PORT, USER_LED_PIN, &user_led_port_pin_cfg);
//
//    for(;;)
//    {
//        // Wait 0.05 [s]
//        Cy_SysTick_DelayInUs(100000);
//        Cy_GPIO_Inv(USER_LED_PORT, USER_LED_PIN);
//    }
  
    uint32_t adc_value = 0;
    int16_t value = 0;
  
    /* Test Vishay 10K */
    Vishay10K ntc_vishay10k = Vishay10K();
    adc_value = 10000;
    value = ntc_vishay10k.GetTemperature(adc_value);
    if(value == 0) return TEST_FAILED;

    /* Test TDK 10K */
    TDK10K ntc_tdk10k = TDK10K();
    adc_value = 10000;
    value = ntc_tdk10k.GetTemperature(adc_value);
    if(value == 0) return TEST_FAILED;
  
    return TEST_SUCCESSFUL;
}

/* [] END OF FILE */
