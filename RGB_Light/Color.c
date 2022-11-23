#include "Color.h"

/* Following RGBW/RGBA format. Each 8 bit long. */
const uint32_t colors_list[COLOR_LIST_LENGHT] = {
    0x00000000, /* OFF */
    0xFFFFFFFF, /* All ON */
    0xFF000000, /* Full red */
    0x00FF0000, /* Full green */
    0x0000FF00, /* Full Blue */
    0x8F00FFFF, /* Violet */
    0xFF00FF00, /* Magenta */
    0xADD8E600  /* Light blue */
};

#ifdef DEBUG_MESSAGES
char* colors_list_name[COLOR_LIST_LENGHT] = {
    "OFF",
    "ON",
    "Full RED",
    "Full GREEN",
    "Full BLUE",
    "Violet",
    "Magenta",
    "Light blue"
};
#endif