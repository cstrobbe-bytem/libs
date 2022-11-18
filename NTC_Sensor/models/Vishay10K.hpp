#include "../NTC_Sensor.hpp"

#define VISHAY_10K_CURVE_LENGTH   156

class Vishay10K : protected NTC_Sensor 
{
    public: 
        Vishay10K();

        int16_t GetTemperature(uint32_t adc_value);
    
    protected:
        /* Protected variables */
        uint32_t ntc_curve[VISHAY_10K_CURVE_LENGTH]; /* Load NTC curve */

};