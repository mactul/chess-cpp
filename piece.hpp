#pragma once

#include <stdint.h>
#include "board.hpp"


class Board;

class Piece {
protected:
    Board* board;
    uint8_t row;
    uint8_t col;
    bool black;

    bool _has_moved = false;

    bool move_no_geometry(uint8_t row, uint8_t col, bool fake = false);

    bool rook_restriction(uint8_t row, uint8_t col) const;
    bool bishop_restriction(uint8_t row, uint8_t col) const;

public:
    Piece(Board* board, uint8_t row, uint8_t col, bool black);
    virtual ~Piece();
    bool is_black() const;

    bool has_moved(void) const;

    bool unrestricted_move(uint8_t row, uint8_t col);  // this unfortunately has to be public

    virtual bool move(uint8_t row, uint8_t col, bool fake = false) = 0;
    virtual const char* display(void) const = 0;
    virtual const char* whoami(void) const = 0;

    virtual Piece* copy(Board* board) const = 0;
};