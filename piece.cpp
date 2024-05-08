#include <iostream>
#include "piece.hpp"
#include "macros.h"

Piece::Piece(Board* board, uint8_t row, uint8_t col, bool black): board(board), row(row), col(col), black(black)
{
}

Piece::~Piece()
{
}

bool Piece::is_black() const
{
    return this->black;
}

bool Piece::move_no_geometry(uint8_t row, uint8_t col, bool fake)
{
    Board board_copy = Board(*(this->board));
    Piece* piece_copy = board_copy.get_piece(this->row, this->col);
    if(piece_copy == nullptr)
    {
        std::cerr << "Fatal error, the impossible happened" << std::endl;
        std::exit(1);
    }


    // if it's a fake move and it kills the adverse king, we have to return true, even if our king is endanger.
    Piece* piece_to_kill = board_copy.get_piece(row, col);
    if(fake && piece_to_kill != nullptr && piece_to_kill->whoami()[1] == 'K' && piece_to_kill->is_black() != this->black)
    {
        return true;
    }


    if(!piece_copy->unrestricted_move(row, col))
    {
        // illegal move
        return false;
    }


    if(board_copy.is_king_in_chess(this->black))
    {
        // king in chess: illegal move
        return false;
    }

    if(fake)
    {
        return true;
    }

    return this->unrestricted_move(row, col);
}


bool Piece::unrestricted_move(uint8_t row, uint8_t col)
{
    Piece* piece = this->board->get_piece(row, col);

    if(piece != nullptr && piece->is_black() == this->black)
    {
        return false;
    }
    if(!this->board->set_piece(row, col, this))
    {
        return false;
    }

    // return values are discared because here we know the data and methods can't fail.

    (void)this->board->set_piece(this->row, this->col, nullptr);
    this->row = row;
    this->col = col;

    (void)this->board->set_en_passant(-1, -1, this->black);

    this->_has_moved = true;

    return true;
}


bool Piece::rook_restriction(uint8_t row, uint8_t col) const
{
    if(this->row == row && this->col == col)
    {
        // a rook can't move to the same position
        return false;
    }
    if(this->row != row && this->col != col)
    {
        return false;
    }

    if(this->row == row)
    {
        for(uint8_t c = MIN(this->col, col)+1; c < MAX(this->col, col); c++)
        {
            if(this->board->get_piece(row, c) != nullptr)
            {
                return false;  // something in the way
            }
        }
    }
    else
    {
        for(uint8_t r = MIN(this->row, row)+1; r < MAX(this->row, row); r++)
        {
            if(this->board->get_piece(r, col) != nullptr)
            {
                return false;  // something in the way
            }
        }
    }

    return true;
}

bool Piece::bishop_restriction(uint8_t row, uint8_t col) const
{
    int16_t row_off = (int16_t)this->row - (int16_t)row;
    int16_t col_off = (int16_t)this->col - (int16_t)col;

    if(this->row == row)
    {
        // a bishop has to move at least by 1 in row.
        return false;
    }

    if(ABS(row_off) != ABS(col_off))
    {
        return false;
    }
    
    for(int i = 1; i < ABS(row_off); i++)
    {
        if(this->board->get_piece(this->row - i * SIGN(row_off), this->col - i * SIGN(col_off)) != nullptr)
        {
            return false;  // something in the way
        }
    }
    return true;
}

bool Piece::has_moved(void) const
{
    return this->_has_moved;
}