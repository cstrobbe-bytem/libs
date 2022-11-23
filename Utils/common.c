#include "common.h"

uint32_t scale_color(uint32_t color_, float scaler_)
{

    uint8_t white = (uint8_t)(((color_ >> 24) * scaler_)/256);
    uint8_t blue  = (uint8_t)(((color_ >> 16) * scaler_)/256);
    uint8_t green = (uint8_t)(((color_ >> 8)  * scaler_)/256);
    uint8_t red   = (uint8_t)((color_ * scaler_)/256);

    uint32_t tmp_color = (white << 24) | 
                         (blue << 16)  | 
                         (green << 8)  | 
                         (red);

    return tmp_color;
}