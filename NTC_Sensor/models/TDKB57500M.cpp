#include "TDKB57500M.hpp"

TDKB57500M::TDKB57500M()
:ntc_curve {
      /* ohm          °C    adc */
      177000,   //   -30
      167680,   //   -29
      158360,   //   -28
      149040,   //   -27
      139720,   //   -26
      130400,   //   -25
      123734,   //   -24
      117068,   //   -23
      110402,   //   -22
      103736,   //   -21
      97070,    //   -20
      92242,    //   -19
      87414,    //   -18
      82586,    //   -17
      77758,    //   -16
      72930,    //   -15
      69410,    //   -14
      65890,    //   -13
      62370,    //   -12
      58850,    //   -11
      55330,    //   -10
      52728,    //    -9
      50126,    //    -8
      47524,    //    -7
      44922,    //    -6
      42320,    //    -5
      40388,    //    -4
      38456,    //    -3
      36524,    //    -2
      34592,    //    -1
      32660,    //     0
      31206,    //     1
      29752,    //     2
      28298,    //     3
      26844,    //     4
      25390,    //     5
      24292,    //     6
      23194,    //     7
      22096,    //     8
      20998,    //     9
      19900,    //    10
      19062,    //    11
      18224,    //    12
      17386,    //    13
      16548,    //    14
      15710,    //    15
      15066,    //    16
      14422,    //    17
      13778,    //    18
      13134,    //    19
      12490,    //    20
      11992,    //    21
      11494,    //    22
      10996,    //    23
      10498,    //    24
      10000,    //    25
      9611,     //    26
      9223,     //    27
      8834,     //    28
      8446,     //    29
      8057,     //    30
      7752,     //    31
      7447,     //    32
      7141,     //    33
      6836,     //    34
      6531,     //    35
      6290,     //    36
      6049,     //    37
      5809,     //    38
      5568,     //    39
      5327,     //    40
      5135,     //    41
      4944,     //    42
      4752,     //    43
      4561,     //    44
      4369,     //    45
      4216,     //    46
      4063,     //    47
      3909,     //    48
      3756,     //    49
      3603,     //    50
      3480,     //    51
      3356,     //    52
      3233,     //    53
      3109,     //    54
      2986,     //    55
      2886,     //    56
      2787,     //    57
      2687,     //    58
      2588,     //    59
      2488,     //    60
      2407,     //    61
      2326,     //    62
      2245,     //    63
      2164,     //    64
      2083,     //    65
      2017,     //    66
      1951,     //    67
      1884,     //    68
      1818,     //    69
      1752,     //    70
      1698,     //    71
      1644,     //    72
      1589,     //    73
      1535,     //    74
      1481,     //    75
      1436,     //    76
      1392,     //    77
      1347,     //    78
      1303,     //    79
      1258,     //    80
      1221,     //    81
      1184,     //    82
      1146,     //    83
      1109,     //    84
      1072,     //    85
      1041,     //    86
      1010,     //    87
      979,      //    88
      949,      //    89
      918,      //    90
      892,      //    91
      866,      //    92
      840,      //    93
      814,      //    94
      789,      //    95
      767,      //    96
      745,      //    97
      723,      //    98
      702,      //    99
      680,      //   100
      662,      //   101
      643,      //   102
      625,      //   103
      607,      //   104
      589,      //   105
      573,      //   106
      558,      //   107
      542,      //   108
      527,      //   109
      511,      //   110
      498,      //   111
      485,      //   112
      472,      //   113
      459,      //   114
      445,      //   115
      434,      //   116
      423,      //   117
      412,      //   118
      401,      //   119
      389,      //   120
      380,      //   121
      370,      //   122
      361,      //   123
      351,      //   124
      342       //   125 (392 +/- 3)
  }
{
    /* Set sensors parameters */
    this->max_temperature = 125; /* [°C] */
    this->min_temperature = -30; /* [°C] */
    this->RA = 390000.0f; /* 390K [ohm] */
    this->RB = 3300.0f;   /* 3K3 [ohm] */
}

int16_t TDKB57500M::GetTemperature(uint32_t adc_value)
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
    
    if((uint32_t)this->ntc_resistance < this->ntc_curve[TDKB57500M_CURVE_LENGTH-1]) 
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
    for (i = 0; i < TDKB57500M_CURVE_LENGTH-2; i++)
    {
        if (this->ntc_resistance > this->ntc_curve[i + 1] && 
            this->ntc_resistance <= this->ntc_curve[i]) break;
    }

    // 2. Interpola fra i due valori:
    //      m = 10 / (tab[i] - tab[i+1)
    //      y = y0 + m * (tab[i] - adc)
    float m = 10.0f / (this->ntc_curve[i] - this->ntc_curve[i+1]);
    float t = 10.0f * ((float)(this->min_temperature) + i) + m * (float)(this->ntc_curve[i] - this->ntc_resistance);

    return (int16_t)t;
}