#include "../NTC_Sensor.hpp"

#define TDK_10K_CURVE_LENGTH   156

class TDK10K : protected NTC_Sensor 
{
    public: 
        TDK10K();

        int16_t GetTemperature(uint32_t adc_value);
    
    protected:
        /* Protected variables */
        uint32_t ntc_curve[TDK_10K_CURVE_LENGTH]; /* Load NTC curve */
};