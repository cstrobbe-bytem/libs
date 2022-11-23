#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define COLOR_LIST_LENGHT   8
#define COLOR_STATES_LENGTH 7

typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t white;
} RGB_color;

typedef enum colors_list_index { 
    COLOR_OFF=0, 
    COLOR_ON,
    COLOR_FULL_RED,
    COLOR_FULL_GREEN,
    COLOR_FULL_BLUE,
    COLOR_VIOLET,
    COLOR_MAGENTA,
    COLOR_LIGHT_BLUE
} colors_list_index;

/* Following RGBW/RGBA format. Each 8 bit long. */
extern const uint32_t colors_list[COLOR_LIST_LENGHT];

#ifdef DEBUG_MESSAGES
char* colors_list_name[COLOR_LIST_LENGHT];
#define print_color_name(color_index) printf("[Color]: %s\n", colors_list_name[color_index])
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* COLOR_H */