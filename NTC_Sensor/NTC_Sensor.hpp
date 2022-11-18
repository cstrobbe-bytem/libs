#ifndef NTC_SENSOR_HPP
#define NTC_SENSOR_HPP

#include "NTC_common.h"
#include "math.h"

/* Schematic */
/*
           VDD
           │             
           │              
         ┌─┴─┐            
         │   │            
         │   │            
         │   │RB          
         │   │            
         │   │              
         └─┬─┘              
           │                
ADC ───────┼────────────────┐
           │                │
         ┌─┴─┐            ┌─┴─┐
         │   │            │   │
         │   │            │   │
         │   │RA          │   │R_NTC
         │   │            │   │
         │   │            │   │
         └─┬─┘            └─┬─┘
           │                │
           ├────────────────┘
           │
           │
           GND
*/

/*
temp1 = 4095 / 2047 (~0.5)
if temp1 < 1.0f sonda aperta???

if RA * temp1 - RA < RB sonda aperta???

Rntc = (RA * RB) / (RA*(temp1-1)-RB)

CRIS

c = VDD / VADC = ADC_STEPS / ADC_VALUE
d = 1 / c
Rntc = (c * RA * RB) * / ( RA * (1 - c) - c * RB )
collect c
Rntc = (RA * RB) * / ( RA/c - RA - RB )
subsitute c = 1 /d
Rntc = (RA * RB) / ( RA * (D - 1) - RB ) // Same as library
*/

#define DEFAULT_ADC_RESOLUTION      12     /* [bit] */
#define DEFAULT_ADC_STEPS           4095   /* [-] */
#define DEFAULT_ADC_VREF            5      /* [V] */
#define NTC_TEMP_GAIN               10     /* Ouput value is multiplied by this gain */

class NTC_Sensor 
{
    public:

        NTC_Sensor(); /* Default constructor */
        
        /**
         * @brief Construct a new ntc sensor object
         * 
         * @param ntc_model 
         */
        NTC_Sensor(NTC_sensor_model ntc_model);

        /**
         * @brief Destroy the ntc sensor object
         * 
         */
        virtual ~NTC_Sensor(){};

        // virtual void Configure(NTC_Sensors_model ntc_model_);

        /**
         * @brief Get the Temperature object
         * 
         * @param adc_value 
         * @return int16_t 
         */
        virtual int16_t GetTemperature(uint32_t adc_value); /* Get temperature given 12bit ADC value*/

        /**
         * @brief 
         * 
         * @param adc_res 
         */
        void SetADCResolution(uint8_t adc_res);
    
        NTC_sensor_model model; /* Store NTC model */
        int min_temperature;    /* Minimum NTC temperature */
        int max_temperature;    /* Maximum NTC temperature */
        float RA;               /* Ground resistor [Ohm] */
        float RB;               /* Vdd resistor [Ohm] */
        float ntc_resistance;   /* NTC resistance [Ohm] */
        uint8_t adc_resolution; /* ADC resolution [bit] */
        float adc_steps;        /* ADC steps (2^adc_resolution) [-] */
        int16_t Tntc;           /* Last computed temperature */
};

#endif /* NTC_SENSOR_HPP */