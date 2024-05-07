#include "pieces/queen.hpp"
#include "macros.h"

Queen::Queen(Board* board, uint8_t row, uint8_t col, bool black): Piece(board, row, col, black)
{
}

bool Queen::move(uint8_t row, uint8_t col, bool fake)
{
    return (this->rook_restriction(row, col) || this->bishop_restriction(row, col)) && this->move_no_geometry(row, col, fake);
}

const char* Queen::display(void) const
{
    #ifdef ONLY_ASCII
        return "Q";
    #else
        if(this->black)
        {
            return UNICODE_BLACK_QUEEN;
        }
        return UNICODE_WHITE_QUEEN;
    #endif
}

const char* Queen::whoami(void) const
{
    if(this->black)
    {
        return "bQ";
    }
    return "wQ";
}


MovementMap Queen::list_maybe_possible_movements() const
{
    return (MovementMap)(-1);  // all possible movements
}

Piece* Queen::copy(Board* board) const
{
    return new Queen(board, this->row, this->col, this->black);
}