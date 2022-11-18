#include "TDK10K.hpp"

TDK10K::TDK10K()
:ntc_curve {
    /* ohm          °C    adc */
    111330,   //   -30
    106376,   //   -29
    101422,   //   -28
    96468,    //   -27
    91514,    //   -26
    86560,    //   -25
    82806,    //   -24
    79052,    //   -23
    75298,    //   -22
    71544,    //   -21
    67790,    //   -20
    64924,    //   -19
    62058,    //   -18
    59192,    //   -17
    56326,    //   -16
    53460,    //   -15
    51258,    //   -14
    49056,    //   -13
    46854,    //   -12
    44652,    //   -11
    42450,    //   -10
    40746,    //    -9
    39042,    //    -8
    37338,    //    -7
    35634,    //    -6
    33930,    //    -5
    32600,    //    -4
    31270,    //    -3
    29940,    //    -2
    28610,    //    -1
    27280,    //     0
    26238,    //     1
    25196,    //     2
    24154,    //     3
    23112,    //     4
    22070,    //     5
    21248,    //     6
    20426,    //     7
    19604,    //     8
    18782,    //     9
    17960,    //    10
    17308,    //    11
    16656,    //    12
    16004,    //    13
    15352,    //    14
    14700,    //    15
    14178,    //    16
    13656,    //    17
    13134,    //    18
    12612,    //    19
    12090,    //    20
    11672,    //    21
    11254,    //    22
    10836,    //    23
    10418,    //    24
    10000,    //    25
    9662,     //    26
    9324,     //    27
    8986,     //    28
    8648,     //    29
    8310,     //    30
    8036,     //    31
    7762,     //    32
    7488,     //    33
    7214,     //    34
    6940,     //    35
    6718,     //    36
    6496,     //    37
    6274,     //    38
    6052,     //    39
    5830,     //    40
    5646,     //    41
    5462,     //    42
    5278,     //    43
    5094,     //    44
    4910,     //    45
    4760,     //    46
    4610,     //    47
    4460,     //    48
    4310,     //    49
    4160,     //    50
    4036,     //    51
    3912,     //    52
    3788,     //    53
    3664,     //    54
    3540,     //    55
    3436,     //    56
    3332,     //    57
    3228,     //    58
    3124,     //    59
    3020,     //    60
    2934,     //    61
    2848,     //    62
    2762,     //    63
    2676,     //    64
    2590,     //    65
    2518,     //    66
    2446,     //    67
    2374,     //    68
    2302,     //    69
    2230,     //    70
    2168,     //    71
    2106,     //    72
    2044,     //    73
    1982,     //    74
    1920,     //    75
    1870,     //    76
    1820,     //    77
    1770,     //    78
    1720,     //    79
    1670,     //    80
    1626,     //    81
    1582,     //    82
    1538,     //    83
    1494,     //    84
    1450,     //    85
    1414,     //    86
    1378,     //    87
    1342,     //    88
    1306,     //    89
    1270,     //    90
    1238,     //    91
    1206,     //    92
    1174,     //    93
    1142,     //    94
    1110,     //    95
    1083,     //    96
    1056,     //    97
    1029,     //    98
    1002,     //    99
    975,      //   100
    952,      //   101
    929,      //   102
    906,      //   103
    883,      //   104
    860,      //   105
    840,      //   106
    820,      //   107
    800,      //   108
    780,      //   109
    760,      //   110
    743,      //   111
    726,      //   112
    708,      //   113
    691,      //   114
    674,      //   115
    659,      //   116
    644,      //   117
    629,      //   118
    614,      //   119
    599,      //   120
    586,      //   121
    573,      //   122
    560,      //   123
    547,      //   124
    534       //   125
} 
{
    /* Set sensors parameters */
    this->max_temperature = 125; /* [°C] */
    this->min_temperature = -30; /* [°C] */
    this->RA = 1000000.0f; /* 1M [ohm] */
    this->RB = 10000.0f;   /* 10K [ohm] */
}

int16_t TDK10K::GetTemperature(uint32_t adc_value)
{
    /* Check table */
    if (!this->ntc_curve) return EMPTY_NTC_TABLE;
    
    /* Check adc value */
    if(adc_value == 0) return NTC_SHORT_CIRCUIT;      

    /* Check if ADC resolution and steps are set */
    if (this->adc_steps == 0 || this->adc_resolution == 0) 
    {
        #ifdef DEBUG_MESSAGES
        print_error_message(NTC_NO_ADC_RES_SET);
        #endif
        return NTC_NO_ADC_RES_SET; // ???
    }

    /* Vadc/Vdd [-] */
    float c = (this->adc_steps / (float)adc_value);

    /* Check NTC shorted to VDD */
    if(c <= 1.0f) /* Vadc > Vdd */
    { 
        #ifdef DEBUG_MESSAGES
        print_error_message(NTC_SHORT_CIRCUIT);
        #endif
        return NTC_OPEN_CIRCUIT; // ???
    }

    /* Compute NTC resistance */
    this->ntc_resistance = (RB * RA) / ((RA * (c - 1.0f)) - RB) ;

    /* Check if resistance value stays inside the table */
    if((uint32_t)this->ntc_resistance > this->ntc_curve[0]) 
    {
        return NTC_OPEN_CIRCUIT;
        #ifdef DEBUG_MESSAGES
        print_error_message(NTC_OPEN_CIRCUIT);
        #endif
    }
    
    /* Short circuit  */
    if((uint32_t)this->ntc_resistance < this->ntc_curve[TDK_10K_CURVE_LENGTH-1]) 
    {
        return NTC_SHORT_CIRCUIT;
        #ifdef DEBUG_MESSAGES
        print_error_message(NTC_SHORT_CIRCUIT);
        #endif
    }

    /* Find temperature */ // Use algorithm ???
    // 1. Cerca l'indice di tabella tale che:
    //      tab[i + 1] < x <= tab[i]
    int i = 0;
    for (i = 0; i < TDK_10K_CURVE_LENGTH-2; i++)
    {
        if (this->ntc_resistance > this->ntc_curve[i + 1] && 
            this->ntc_resistance <= this->ntc_curve[i]) break;
    }

    // 2. Interpola fra i due valori:
    //      m = 10 / (tab[i] - tab[i+1)
    //      y = y0 + m * (tab[i] - adc)
    // float m = 10.0f / (this->ntc_curve[i] - this->ntc_curve[i+1]);
    // float t = 10.0f * ((float)(this->min_temperature + i)) + m * (float)(this->ntc_curve[i] - this->ntc_resistance);

    /* Linear Interpolation */
    // m = (Rntc - R0)/(R1 - R0)
    // Tntc = T0 + m
    this->Tntc = (int16_t)(NTC_TEMP_GAIN * (float)(this->min_temperature + i) + (this->ntc_resistance - this->ntc_curve[i+1])/(this->ntc_curve[i] - this->ntc_curve[i+1]));

    /* Example using NTC_TEMP_GAIN */
    // (float)32.6 °C -> 326 (int16_t)

    return this->Tntc;
}