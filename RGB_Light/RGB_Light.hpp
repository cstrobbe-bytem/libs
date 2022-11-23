#ifndef RGB_LIGHT_HPP
#define RGB_LIGHT_HPP

#include "Color.h"
#include "Fade.hpp"
#include "color_states.h"

#define TIMER_OVERFLOW_CNT         1000
#define TIMER_CNT_STEPS_PER_CYCLE  1

class RGB_Light : public ColorFade
{
    public:
        RGB_Light();

        ~RGB_Light(){};

        /**
         * @brief Update led light. If no new_state is set then no update will be performed.
         * 
         * @param new_state 
         */
        virtual void SetState(color_states_t new_state=COLOR_STATE_DEFAULT);

        virtual float GetPWM();

        virtual void TimerCallback(void)
        {
            this->timer_cnt = (this->timer_cnt+TIMER_CNT_STEPS_PER_CYCLE) / TIMER_OVERFLOW_CNT;
        }

        inline void SetTimer(uint16_t timer_) { this->timer_cnt = timer_; };

        inline void ResetTimer() { this->timer_cnt = 0; };
        
    private:
        uint16_t timer_cnt; /* Internal counter */
        color_states_t actual_state; /* Actual/Last color state */

        void _SetState(color_state_t *state_);
};

#endif /* RGB_LIGHT_HPP */