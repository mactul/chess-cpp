#include "pieces/knight.hpp"
#include "macros.h"

Knight::Knight(Board* board, uint8_t row, uint8_t col, bool black): Piece(board, row, col, black)
{
}

bool Knight::move(uint8_t row, uint8_t col, bool fake)
{
    int16_t row_off = ABS((int16_t)this->row - (int16_t)row);
    int16_t col_off = ABS((int16_t)this->col - (int16_t)col);

    if((row_off != 1 || col_off != 2) && (row_off != 2 || col_off != 1))
    {
        return false;
    }

    return this->move_no_geometry(row, col, fake);
}

const char* Knight::display(void) const
{
    #ifdef ONLY_ASCII
        return "N";
    #else
        if(this->black)
        {
            return UNICODE_BLACK_KNIGHT;
        }
        return UNICODE_WHITE_KNIGHT;
    #endif
}

const char* Knight::whoami(void) const
{
    if(this->black)
    {
        return "bN";
    }
    return "wN";
}

MovementMap Knight::list_maybe_possible_movements() const
{
    return (MovementMap)(-1);  // all possible movements
}

Piece* Knight::copy(Board* board) const
{
    return new Knight(board, this->row, this->col, this->black);
}