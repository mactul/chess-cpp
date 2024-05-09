#include <iostream>
#if defined(_WIN32) || defined(WIN32)
    #include <windows.h>
#endif
#include "color_display.hpp"

void print_in_color(const char* str, enum COLORS color)
{
    #if defined(_WIN32) || defined(WIN32)
        static HANDLE  hConsole = NULL;
        WORD windows_color_code = 0;
        switch(color)
        {
            case COLOR_BLACK_ON_GREEN:
                windows_color_code = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
                break;
            case COLOR_BLACK_ON_WHITE:
                windows_color_code = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
                break;
            case COLOR_WHITE_ON_BLACK:
                windows_color_code = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
                break;
            case COLOR_GREY_ON_GREEN:
                windows_color_code = BACKGROUND_GREEN | BACKGROUND_INTENSITY | FOREGROUND_INTENSITY;
                break;
            case COLOR_GREY_ON_WHITE:
                windows_color_code = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_INTENSITY;
                break;
        }

        if(hConsole == NULL)
        {
            SetConsoleOutputCP(CP_UTF8);
            SetConsoleCP(CP_UTF8);

            hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        }
        SetConsoleTextAttribute(hConsole, windows_color_code);
        std::cout << " " << str << " ";
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    #else
        const char* linux_color_code = NULL;
        switch(color)
        {
            case COLOR_BLACK_ON_GREEN:
                linux_color_code = "42;30m";
                break;
            case COLOR_BLACK_ON_WHITE:
                linux_color_code = "47;30m";
                break;
            case COLOR_WHITE_ON_BLACK:
                linux_color_code = "40;37m";
                break;
            case COLOR_GREY_ON_GREEN:
                linux_color_code = "42;90m";
                break;
            case COLOR_GREY_ON_WHITE:
                linux_color_code = "47;90m";
                break;
        }
        std::cout << "\033[" << linux_color_code << " " << str << " \033[0m";
    #endif
}