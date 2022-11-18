/*
 * NTC sensor template
*/
#include "NTC_Sensor.hpp"

NTC_Sensor::NTC_Sensor()
:adc_resolution(DEFAULT_ADC_RESOLUTION), adc_steps(DEFAULT_ADC_STEPS)
{}

NTC_Sensor::NTC_Sensor(NTC_sensor_model ntc_model)
:model(ntc_model), adc_resolution(DEFAULT_ADC_RESOLUTION),  adc_steps(DEFAULT_ADC_STEPS)
{}

int16_t NTC_Sensor::GetTemperature(uint32_t adc_value)
{ 
    #ifdef DEBUG_MESSAGES
    print_error_message(NO_NTC_IMPLEMENTATION);
    #endif
    return 0;
}

void NTC_Sensor::SetADCResolution(uint8_t adc_res)
{
    this->adc_resolution = adc_res;
    this->adc_steps = pow(adc_res, 2);
}
    