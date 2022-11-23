#include "Fade.hpp"

#include "Color.h"

ColorFade::ColorFade()
:enable{false}, 
scaler_step{DEFAULT_SCALER_STEP},
min_scaler{DEFAULT_MIN_SCALER},
scaler{1.0f},
color{0x00000000}
{}

uint32_t ColorFade::Update()
{
    /* Check fade enable */
    if(this->enable)
    {
        /* Check null color */
        if (!this->color == 0x00000000)
        {
            /* Update scaler */
            this->scaler += this->scaler_step;
            if ((this->scaler >= 1.0f) || (this->scaler <= this->min_scaler))
            {            
                this->scaler_step *= -1;
                this->scaler += this->scaler_step;
            }

            /* Scale color */
            this->_ScaleActualColor(this->scaler);

            return this->tmp_color;
        }
        else
        {
            return 0x00000000; /* No color available */
        }
    }
    else 
    {
        return 0x00000000; /* Fader is disabled */
    }
}

float ColorFade::UpdateScaler()
{
    /* Check fade enable */
    if(this->enable)
    {
        /* Check null color */
        if (!this->color == 0x00000000)
        {
            /* Update scaler */
            this->scaler += this->scaler_step;
            if ((this->scaler >= 1.0f) || (this->scaler <= this->min_scaler))
            {            
                this->scaler_step *= -1;
                this->scaler += this->scaler_step;
            }

            return this->scaler;
        }
        else
        {
            return 0.0f; /* No color available */
        }
    }
    else 
    {
        return 0.0f; /* Fader is disabled */
    }
}

void ColorFade::_ScaleActualColor(float scaler_)
{
    uint32_t tmp_color = this->color;

    this->rgbw_tmp_color.white = (uint8_t)((tmp_color >> 24) * scaler_)/256;
    this->rgbw_tmp_color.blue  = (uint8_t)((tmp_color >> 16)  * scaler_)/256;
    this->rgbw_tmp_color.green = (uint8_t)((tmp_color >> 8) * scaler_)/256;
    this->rgbw_tmp_color.red   = (uint8_t)(tmp_color * scaler_)/256;

    this->tmp_color = (this->rgbw_tmp_color.white << 24) | 
                      (this->rgbw_tmp_color.blue << 16)  | 
                      (this->rgbw_tmp_color.green << 8)  | 
                      (this->rgbw_tmp_color.red);
}

