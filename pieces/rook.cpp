#include "pieces/rook.hpp"
#include "macros.h"

Rook::Rook(Board* board, uint8_t row, uint8_t col, bool black): Piece(board, row, col, black)
{
}

bool Rook::move(uint8_t row, uint8_t col, bool fake)
{
    return this->rook_restriction(row, col) && ((fake && this->fake_unrestricted_move(row, col)) || this->unrestricted_move(row, col));
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

bool Rook::has_possible_movements(void) const
{
    if(this->fake_unrestricted_move(this->row, this->col - 1))
    {
        return true;
    }
    if(this->fake_unrestricted_move(this->row, this->col + 1))
    {
        return true;
    }
    if(this->fake_unrestricted_move(this->row - 1, this->col))
    {
        return true;
    }
    if(this->fake_unrestricted_move(this->row + 1, this->col))
    {
        return true;
    }

    return false;
}

Piece* Rook::copy(Board* board) const
{
    return new Rook(board, this->row, this->col, this->black);
}