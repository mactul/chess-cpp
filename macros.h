/**
 * @file macros.h
 * @brief This file regroups some macros that are useful all accros the project.
 * 
 */

#pragma once

#define ABS(x) ((x) < 0 ? -(x): (x))
#define SIGN(x) ((x) < 0 ? -1: 1)

#define MAX(x, y) ((x) > (y) ? (x): (y))
#define MIN(x, y) ((x) < (y) ? (x): (y))

#define UNICODE_WHITE_KING "\u2654"
#define UNICODE_WHITE_QUEEN "\u2655"
#define UNICODE_WHITE_ROOK "\u2656"
#define UNICODE_WHITE_BISHOP "\u2657"
#define UNICODE_WHITE_KNIGHT "\u2658"
#define UNICODE_WHITE_PAWN "\u2659"

#define UNICODE_BLACK_KING "\u265A"
#define UNICODE_BLACK_QUEEN "\u265B"
#define UNICODE_BLACK_ROOK "\u265C"
#define UNICODE_BLACK_BISHOP "\u265D"
#define UNICODE_BLACK_KNIGHT "\u265E"
#define UNICODE_BLACK_PAWN "\u265F"