#include "pieces/bishop.hpp"
#include "macros.h"

Bishop::Bishop(Board* board, uint8_t row, uint8_t col, bool black): Piece(board, row, col, black)
{
}

bool Bishop::move(uint8_t row, uint8_t col, bool fake)
{
    return this->bishop_restriction(row, col) && this->move_no_geometry(row, col, fake);
}

const char* Bishop::display(void) const
{
    #ifdef ONLY_ASCII
        return "B";
    #else
        if(this->black)
        {
            return UNICODE_BLACK_BISHOP;
        }
        return UNICODE_WHITE_BISHOP;
    #endif
}

const char* Bishop::whoami(void) const
{
    if(this->black)
    {
        return "bB";
    }
    return "wB";
}



Piece* Bishop::copy(Board* board) const
{
    return new Bishop(board, this->row, this->col, this->black);
}