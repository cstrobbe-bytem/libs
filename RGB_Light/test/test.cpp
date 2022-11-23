/**
* \file test_cm4.cpp
*
* \brief
* Main file for CM4
*
*******************************************************************************/

//#include "cy_project.h"
//#include "cy_device_headers.h"

#include "board.hpp"
#include "../../utils/common.h"

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

int test(void)
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
  
    /* Instantiation. Configuration on deafault values. Fade disabled by default. */
    RGB_Light test_light = RGB_Light();
    
    /* User configuration */
    /* 1. Set state from color_states.c */
    test_light.SetState(COLOR_STATE_ERROR);

    /* 3.  */


    /* User interface. Once configured. */
    // Set new state
    // Get new/old pwm value or scaled color
    // Timer callback routine
    
    /* Set timer callback */
    
    for(int i=0; i< NUM_OF_TESTS; i++)
    {
        float color_scaler = test_light.GetPWM();
        for(int i=0; i< NUM_OF_TESTS; i++)
        {
            /* Update timer callcak */
            test_light.TimerCallback();
        }
    }
    
  
    return TEST_SUCCESSFUL;
}

/* [] END OF FILE */
