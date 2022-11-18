#include "Vishay10K.hpp"

Vishay10K::Vishay10K()
:ntc_curve{ 
      /* ohm          °C    adc */
      135452,   //   -30    3918 (+/- 4)
      127837,   //   -29
      120707,   //   -28
      114028,   //   -27
      107768,   //   -26
      101898,   //   -25
      96391,    //   -24
      91222,    //   -23
      86369,    //   -22
      81809,    //   -21
      77523,    //   -20
      73492,    //   -19
      69701,    //   -18
      66132,    //   -17
      62771,    //   -16
      59606,    //   -15
      56623,    //   -14
      53810,    //   -13
      51157,    //   -12
      48654,    //   -11
      46290,    //   -10
      44058,    //    -9
      41950,    //    -8
      39957,    //    -7
      38072,    //    -6
      36290,    //    -5
      34603,    //    -4
      33006,    //    -3
      31494,    //    -2
      30062,    //    -1
      28704,    //     0
      27417,    //     1
      26197,    //     2
      25039,    //     3
      23940,    //     4
      22897,    //     5
      21906,    //     6
      20964,    //     7
      20070,    //     8
      19219,    //     9
      18410,    //    10
      17641,    //    11
      16909,    //    12
      16212,    //    13
      15548,    //    14
      14916,    //    15
      14313,    //    16
      13739,    //    17
      13192,    //    18
      12669,    //    19
      12171,    //    20
      11696,    //    21
      11242,    //    22
      10809,    //    23
      10395,    //    24
      10000,    //    25
      9622,     //    26
      9261,     //    27
      8916,     //    28
      8585,     //    29
      8269,     //    30
      7967,     //    31
      7678,     //    32
      7400,     //    33
      7135,     //    34
      6881,     //    35
      6637,     //    36
      6403,     //    37
      6179,     //    38
      5965,     //    39
      5759,     //    40
      5561,     //    41
      5372,     //    42
      5189,     //    43
      5015,     //    44
      4847,     //    45
      4686,     //    46
      4531,     //    47
      4382,     //    48
      4239,     //    49
      4101,     //    50
      3969,     //    51
      3842,     //    52
      3719,     //    53
      3601,     //    54
      3488,     //    55
      3379,     //    56
      3274,     //    57
      3172,     //    58
      3075,     //    59
      2981,     //    60
      2890,     //    61
      2803,     //    62
      2719,     //    63
      2638,     //    64
      2559,     //    65
      2484,     //    66
      2411,     //    67
      2341,     //    68
      2273,     //    69
      2207,     //    70
      2144,     //    71
      2083,     //    72
      2024,     //    73
      1967,     //    74
      1912,     //    75
      1858,     //    76
      1807,     //    77
      1757,     //    78
      1709,     //    79
      1662,     //    80
      1617,     //    81
      1574,     //    82
      1532,     //    83
      1491,     //    84
      1451,     //    85
      1413,     //    86
      1376,     //    87
      1340,     //    88
      1305,     //    89
      1272,     //    90
      1239,     //    91
      1208,     //    92
      1177,     //    93
      1147,     //    94
      1118,     //    95
      1091,     //    96
      1063,     //    97
      1037,     //    98
      1012,     //    99
      987,      //   100
      963,      //   101
      940,      //   102
      917,      //   103
      895,      //   104
      874,      //   105
      853,      //   106
      833,      //   107
      814,      //   108
      795,      //   109
      776,      //   110
      758,      //   111
      741,      //   112
      724,      //   113
      708,      //   114
      692,      //   115
      676,      //   116
      661,      //   117
      646,      //   118
      632,      //   119
      618,      //   120
      604,      //   121
      591,      //   122
      578,      //   123
      566,      //   124
      554       //   125    435 (+/- 3)
}
{
    /* Set sensors parameters */
    this->max_temperature = 125; /* [°C] */
    this->min_temperature = -30; /* [°C] */
    this->RA = 390000.0f; /* 390K [ohm] */
    this->RB = 4700.0f;   /* 4K7 [ohm] */
}

int16_t Vishay10K::GetTemperature(uint32_t adc_value)
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

    /* Check NTC shorted to VDD */
    float temp1 = (this->adc_steps / (float)adc_value);
    if(temp1 <= 1.0f)
    { 
        #ifdef DEBUG_MESSAGES
        print_error_message(NTC_SHORT_CIRCUIT);
        #endif
        return NTC_OPEN_CIRCUIT; // ???
    }

    if((RA * (temp1 - 1.0f)) <= RB ) 
    {
        return NTC_OPEN_CIRCUIT; // ???
        #ifdef DEBUG_MESSAGES
        print_error_message(NTC_OPEN_CIRCUIT);
        #endif
    }

    /* Compute NTC resistance */
    this->ntc_resistance = (RB * RA) / ((RA * (temp1 - 1.0f)) - RB) ;

    /* Check if resistance value stays inside the table */
    if((uint32_t)this->ntc_resistance > this->ntc_curve[0]) 
    {
        return NTC_OPEN_CIRCUIT; // ???
        #ifdef DEBUG_MESSAGES
        print_error_message(NTC_OPEN_CIRCUIT);
        #endif
    }
    
    if((uint32_t)this->ntc_resistance < this->ntc_curve[VISHAY_10K_CURVE_LENGTH-1]) 
    {
        return NTC_SHORT_CIRCUIT; // ???
        #ifdef DEBUG_MESSAGES
        print_error_message(NTC_SHORT_CIRCUIT);
        #endif
    }

    /* Find temperature */ // Use algorithm ???
    // 1. Cerca l'indice di tabella tale che:
    //      tab[i + 1] < x <= tab[i]
    int i = 0;
    for (i = 0; i < VISHAY_10K_CURVE_LENGTH-2; i++)
    {
        if (this->ntc_resistance > this->ntc_curve[i + 1] && 
            this->ntc_resistance <= this->ntc_curve[i]) break;
    }

    // 2. Interpola fra i due valori:
    //      m = 10 / (tab[i] - tab[i+1)
    //      y = y0 + m * (tab[i] - adc)
    float m = 10.0f / (this->ntc_curve[i] - this->ntc_curve[i+1]);
    float t = 10.0f * ((float)(this->min_temperature + i)) + m * (float)(this->ntc_curve[i] - this->ntc_resistance);

    return (int16_t)t;
}