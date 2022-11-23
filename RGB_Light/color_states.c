#include "color_states.h"
#include "Color.h"

void fill_colors_states_map()
{
    colors_states_map[COLOR_STATE_DEFAULT]                = {COLOR_OFF,        "default", 0};
    colors_states_map[COLOR_STATE_ERROR]                  = {COLOR_FULL_RED,   "error"  , 1000};
    colors_states_map[COLOR_STATE_STANDBY]                = {COLOR_VIOLET,     "standby", 5000};
    colors_states_map[COLOR_STATE_WAIT_CREDIT]            = {COLOR_LIGHT_BLUE, "wait_credit", 0};
    colors_states_map[COLOR_STATE_GET_PRODUCT]            = {COLOR_FULL_GREEN, "get_product", 500};
    colors_states_map[COLOR_STATE_GET_PRODUCT_AND_CHANGE] = {COLOR_FULL_GREEN, "get_product_and_change", 1000};
    colors_states_map[COLOR_STATE_ENERGY_SAVING]          = {COLOR_OFF,        "energy_saving", 0};
};