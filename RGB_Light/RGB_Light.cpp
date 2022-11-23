#include "RGB_Light.hpp"

RGB_Light::RGB_Light()
:actual_state{COLOR_STATE_DEFAULT}, 
timer_cnt {0}
{
   this->ColorFade::Disable(); /* Disable fade */
}

void RGB_Light::_SetState(color_state_t *state_)
{
    this->ColorFade::SetColor(colors_list[state_->color_list_index]);

    if(state_->timer_period > 0) {
        this->ColorFade::Enable();
        this->ColorFade::SetPeriod(state_->timer_period);
    }
    else {
        this->ColorFade::Disable();
        this->ColorFade::SetPeriod(state_->timer_period);
    }
}

void RGB_Light::SetState(color_states_t new_state)
{
    switch (new_state)
    {
        case COLOR_STATE_DEFAULT:
        {
            color_state_t tmp_var = colors_states_map[COLOR_STATE_DEFAULT];
            this->_SetState(&tmp_var);
            break;
        }

        case COLOR_STATE_ERROR:
        {
            color_state_t tmp_var = colors_states_map[COLOR_STATE_ERROR];
            this->_SetState(&tmp_var);
            break;
        }

        case COLOR_STATE_STANDBY:
        {
            color_state_t tmp_var = colors_states_map[COLOR_STATE_STANDBY];
            this->_SetState(&tmp_var);
            break;
        }

        case COLOR_STATE_WAIT_CREDIT:
        {
            color_state_t tmp_var = colors_states_map[COLOR_STATE_WAIT_CREDIT];
            this->_SetState(&tmp_var);
            break;
        }

        case COLOR_STATE_GET_PRODUCT:
        {
            color_state_t tmp_var = colors_states_map[COLOR_STATE_GET_PRODUCT];
            this->_SetState(&tmp_var);
            break;
        }

        case COLOR_STATE_GET_PRODUCT_AND_CHANGE:
        {
            color_state_t tmp_var = colors_states_map[COLOR_STATE_GET_PRODUCT_AND_CHANGE];
            this->_SetState(&tmp_var);
            break;
        }

        case COLOR_STATE_ENERGY_SAVING:
        {
            color_state_t tmp_var = colors_states_map[COLOR_STATE_ENERGY_SAVING];
            this->_SetState(&tmp_var);
            break;
        }
        
        default:
            break;
    }
}

float RGB_Light::GetPWM()
{
    if(this->ColorFade::IsEnable())
        return this->ColorFade::UpdateScaler();
    else
        return 0.0f;
}