#include "pieces/king.hpp"
#include "macros.h"

King::King(Board* board, uint8_t row, uint8_t col, bool black): Piece(board, row, col, black)
{
}

bool King::move(uint8_t row, uint8_t col, bool fake)
{
    int16_t row_off = ABS((int16_t)this->row - (int16_t)row);
    int16_t col_off = ABS((int16_t)this->col - (int16_t)col);

    if(row_off == 0 && col_off == 0)
    {
        return false;
    }
    if((row_off != 0 && row_off != 1) || (col_off != 0 && col_off != 1))
    {
        return false;
    }
    
    return this->move_no_geometry(row, col, fake);
}

const char* King::display(void) const
{
    #ifdef ONLY_ASCII
        return "K";
    #else
        if(this->black)
        {
            return UNICODE_BLACK_KING;
        }
        return UNICODE_WHITE_KING;
    #endif
}

const char* King::whoami(void) const
{
    if(this->black)
    {
        return "bK";
    }
    return "wK";
}

MovementMap King::list_maybe_possible_movements() const
{
    return (MovementMap)(-1);  // all possible movements
}

Piece* King::copy(Board* board) const
{
    return new King(board, this->row, this->col, this->black);
}