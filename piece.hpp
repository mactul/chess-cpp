#pragma once

#include <stdint.h>
#include "board.hpp"

typedef struct _movement {
    uint8_t dest_row;
    uint8_t dest_col;
} Movement;

class Board;

class Piece {
protected:
    Board* board;
    uint8_t row;
    uint8_t col;
    bool black;

    bool _has_moved = false;

    bool fake_unrestricted_move(uint8_t row, uint8_t col) const;

    bool rook_restriction(uint8_t row, uint8_t col) const;
    bool bishop_restriction(uint8_t row, uint8_t col) const;

public:
    Piece(Board* board, uint8_t row, uint8_t col, bool black);
    virtual ~Piece();
    bool is_black() const;

    bool has_moved(void) const;

    bool unrestricted_move(uint8_t row, uint8_t col);  // this unfortunately has to be public for the class Board

    virtual bool move(uint8_t row, uint8_t col, bool fake = false) = 0;
    virtual const char* display(void) const = 0;
    virtual const char* whoami(void) const = 0;
    virtual bool has_possible_movements(void) const = 0;

    virtual Piece* copy(Board* board) const = 0;
};