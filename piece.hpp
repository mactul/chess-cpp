#pragma once

#include <stdint.h>
#include "board.hpp"


typedef uint64_t MovementMap;

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

    /**
     * @brief This function is here to accelerate checkmate/stalemate calculs by filtering the positions where a piece can go.  
     * @brief If this function always returns `(MovementMap)(-1)` then all positions will be tested and their is no acceleration at all but the program will work.
     * 
     * @return MovementMap - a 8x8 bit field
     */
    virtual MovementMap list_maybe_possible_movements() const = 0;

    virtual Piece* copy(Board* board) const = 0;
};