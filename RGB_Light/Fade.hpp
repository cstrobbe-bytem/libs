#ifndef COLOR_FADE_HPP
#define COLOR_FADE_HPP

#define DEFAULT_MIN_SCALER   0.2f
#define DEFAULT_SCALER_STEP  0.05f

#include <stdint.h>
#include "Color.h"

class ColorFade
{
    public:

        ColorFade();

        ~ColorFade(){};

        /**
         * @brief Compute new scaler and return scaled color.
         * 
         * @return uint32_t scaled color.
         */
        uint32_t Update();

        /**
         * @brief Update scaler according to step [-] and range [min_scaler, 1.0f].
         * 
         * @return float Actual scaler value [min_scaler, 1.0f]
         */
        float UpdateScaler();

        /**
         * @brief Enable fading operation otherwise scaler will be 0.0f.
         * 
         */
        inline void Enable(){ this->enable = true; };

        inline void Disable(){ this->enable = false; };

        /**
         * @brief Set the color variable. Needed by Update().
         * 
         * @param color_ 
         */
        inline void SetColor(uint32_t color_){ this->color = color_; };

        /**
         * @brief Set the min_scaler variable.
         * 
         * @param min_ 
         */
        inline void SetMin(float min_){ this->min_scaler = min_; };

        /**
         * @brief Set the step per cycle variable which represent the increment of the 
         * scaler variable during the Update(), UpdateScaler().
         * 
         * @param step_ 
         */
        inline void SetPeriod(float step_){ this->scaler_step = step_; };

        /**
         * @brief Return if fade is enabled
         * 
         */
        inline bool IsEnable(){ return this->enable; };

    protected:
        bool enable;
        float scaler; /* Actual color scaler */
        float scaler_step;
        float min_scaler;

        /* Colors */
        uint32_t color;           /* Initial color */
        uint32_t tmp_color;       /* Scaled color */
        RGB_color rgbw_tmp_color; /* Scaled color */

        /**
         * @brief Scale intensity of color by scaler_.
         * 
         * @param scaler_  [min_scaler, 1.0f]
         */
        void _ScaleActualColor(float scaler_);

};

#endif /* COLOR_FADE_HPP */