#ifndef COLOR_STATES_H
#define COLOR_STATES_H

#ifdef __cplusplus
extern "C" {
#endif

#define NUM_OF_COLOR_STATES 7

typedef enum {
    COLOR_STATE_DEFAULT=0,
    COLOR_STATE_ERROR,
    COLOR_STATE_STANDBY,
    COLOR_STATE_WAIT_CREDIT,
    COLOR_STATE_GET_PRODUCT,
    COLOR_STATE_GET_PRODUCT_AND_CHANGE,
    COLOR_STATE_ENERGY_SAVING
} color_states_t;

/* Define color state attributes */
typedef struct {
    int color_list_index;  /* Color list index */
    char* color_state;     /* State name */
    uint16_t timer_period; /* Fade period [ms] */
} color_state_t;

/* Collections of colors states */
extern color_state_t colors_states_map[NUM_OF_COLOR_STATES];

void fill_colors_states_map(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* COLOR_STATES_H */