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
    if(fake)
    {
        return this->fake_unrestricted_move(row, col);
    }
    return this->unrestricted_move(row, col);
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

bool King::has_possible_movements(void) const
{
    for(int row_off = -1; row_off <= 1; row_off++)
    {
        for(int col_off = -1; col_off <= 1; col_off++)
        {
            if(this->fake_unrestricted_move(this->row + row_off, this->col + col_off))
            {
                return true;
            }
        }
    }
    return false;
}

Piece* King::copy(Board* board) const
{
    return new King(board, this->row, this->col, this->black);
}