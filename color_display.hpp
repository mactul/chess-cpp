#pragma once

enum COLORS {
    COLOR_BLACK_ON_WHITE,
    COLOR_WHITE_ON_BLACK,
    COLOR_BLACK_ON_GREEN,
    COLOR_GREY_ON_GREEN,
    COLOR_GREY_ON_WHITE
};

void print_in_color(const char* str, enum COLORS color);