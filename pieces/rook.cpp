#include "pieces/rook.hpp"
#include "macros.h"

Rook::Rook(Board* board, uint8_t row, uint8_t col, bool black): Piece(board, row, col, black)
{
}

bool Rook::move(uint8_t row, uint8_t col, bool fake)
{
    return this->rook_restriction(row, col) && this->move_no_geometry(row, col, fake);
}

const char* Rook::display(void) const
{
    #ifdef ONLY_ASCII
        return "R";
    #else
        if(this->black)
        {
            return UNICODE_BLACK_ROOK;
        }
        return UNICODE_WHITE_ROOK;
    #endif
}

const char* Rook::whoami(void) const
{
    if(this->black)
    {
        return "bR";
    }
    return "wR";
}

MovementMap Rook::list_maybe_possible_movements() const
{
    return (MovementMap)(-1);  // all possible movements
}

Piece* Rook::copy(Board* board) const
{
    return new Rook(board, this->row, this->col, this->black);
}