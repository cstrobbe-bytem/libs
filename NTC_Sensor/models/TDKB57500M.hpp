#include "../NTC_Sensor.hpp"

#define TDKB57500M_CURVE_LENGTH   156

class TDKB57500M : protected NTC_Sensor 
{
    public: 
        TDKB57500M();

        int16_t GetTemperature(uint32_t adc_value);
    
    protected:
        /* Protected variables */
        uint32_t ntc_curve[TDKB57500M_CURVE_LENGTH]; /* Load NTC curve */
};