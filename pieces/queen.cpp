#include "pieces/queen.hpp"
#include "macros.h"

Queen::Queen(Board* board, uint8_t row, uint8_t col, bool black): Piece(board, row, col, black)
{
}

bool Queen::move(uint8_t row, uint8_t col, bool fake)
{
    return (this->rook_restriction(row, col) || this->bishop_restriction(row, col)) && ((fake && this->fake_unrestricted_move(row, col)) || this->unrestricted_move(row, col));
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

bool Queen::has_possible_movements(void) const
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

Piece* Queen::copy(Board* board) const
{
    return new Queen(board, this->row, this->col, this->black);
}