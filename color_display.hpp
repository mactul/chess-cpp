#pragma once

enum COLORS {
    COLOR_BLACK_ON_WHITE,
    COLOR_WHITE_ON_BLACK,
    COLOR_BLACK_ON_GREEN,
    COLOR_GREY_ON_GREEN,
    COLOR_GREY_ON_WHITE
};

/**
 * @brief This function display a string, with a space at the left and a space at the right with one of the color in `enum COLORS`.  
 * @brief This function is meant to be Windows and Unix-like compatible.
 * 
 * @param str the string to display.
 * @param color either `COLOR_BLACK_ON_WHITE`, `COLOR_WHITE_ON_BLACK`, `COLOR_BLACK_ON_GREEN`, `COLOR_GREY_ON_GREEN` or `COLOR_GREY_ON_WHITE`.
 */
void print_in_color(const char* str, enum COLORS color);