#include <iostream>
#include <cstdio>
#include "pieces/pawn.hpp"
#include "pieces/queen.hpp"
#include "pieces/rook.hpp"
#include "pieces/bishop.hpp"
#include "pieces/knight.hpp"
#include "macros.h"

Pawn::Pawn(Board* board, uint8_t row, uint8_t col, bool black, bool no_promotion): Piece(board, row, col, black), no_promotion(no_promotion)
{
}


bool Pawn::move(uint8_t row, uint8_t col, bool fake)
{
    bool two_squares_move = false;

    if(this->black)
    {
        if((this->_has_moved && this->row+1 != row) || (!this->_has_moved && this->row+1 != row && (this->row+2 != row || this->col != col)))
        {
            return false;
        }
    }
    else
    {
        if((this->_has_moved && this->row != row+1) || (!this->_has_moved && this->row != row+1 && (this->row != row+2 || this->col != col)))
        {
            return false;
        }
    }

    if(col == this->col)
    {
        if(this->row == row+2 && this->board->get_piece(row+1, col) != nullptr)
        {
            return false;  // something is in the way
        }
        if(this->row+2 == row && this->board->get_piece(this->row+1, col) != nullptr)
        {
            return false;  // something is in the way
        }
        if(this->board->get_piece(row, col) != nullptr)
        {
            return false;
        }  
    }
    else if(col == this->col+1 || col+1 == this->col)
    {
        Piece* piece = this->board->get_piece(row, col);
        if(piece == nullptr || piece->is_black() == this->black)
        {
            if(this->board->is_en_passant(row, col, !this->black))
            {
                this->board->set_piece(row + (!this->black ? 1: -1), col, nullptr);
            }
            else
            {
                return false;
            }
        }
    }
    else
    {
        return false;
    }

    if(fake)
    {
        return this->fake_unrestricted_move(row, col);
    }

    if(this->row == row+2 || this->row+2 == row)
    {
        two_squares_move = true;
    }

    if(this->unrestricted_move(row, col))
    {
        if(!this->no_promotion && ((this->black && row == BOARD_SIZE-1) || (!this->black && row == 0)))
        {
            // promotion
            char answer[20];
            char piece_type = 0;
            std::cout << "Promotion ! ";
            while(piece_type != 'Q' && piece_type != 'R' && piece_type != 'B' && piece_type != 'N')
            {
                std::cout << "To which piece do you want to promote your pawn ? (Q, R, B, N): " << std::flush;
                fgets(answer, 20, stdin);
                piece_type = answer[0];
            }

            Piece* piece;
            switch(piece_type)
            {
                case 'Q':
                    piece = new Queen(this->board, this->row, this->col, this->black);
                    break;
                case 'R':
                    piece = new Rook(this->board, this->row, this->col, this->black);
                    break;
                case 'B':
                    piece = new Bishop(this->board, this->row, this->col, this->black);
                    break;
                case 'N':
                    piece = new Knight(this->board, this->row, this->col, this->black);
                    break;
                default:
                    std::cerr << "Fatal error, the impossible happened" << std::endl;
                    std::exit(1);
            }
            this->board->set_piece(this->row, this->col, piece);
        }
        if(two_squares_move)
        {
            this->board->set_en_passant(this->row + (this->black ? -1: 1), this->col, this->black);
        }
        return true;
    }
    return false;
}

const char* Pawn::display(void) const
{
    #ifdef ONLY_ASCII
        return "P";
    #else
        if(this->black)
        {
            return UNICODE_BLACK_PAWN;
        }
        return UNICODE_WHITE_PAWN;
    #endif
}

const char* Pawn::whoami(void) const
{
    if(this->black)
    {
        return "bP";
    }
    return "wP";
}

bool Pawn::has_possible_movements(void) const
{
    if(this->fake_unrestricted_move(this->row + (this->black ? 1: -1), this->col))
    {
        return true;
    }
    if(this->fake_unrestricted_move(this->row + (this->black ? 1: -1), this->col + 1))
    {
        return true;
    }
    if(this->fake_unrestricted_move(this->row + (this->black ? 1: -1), this->col - 1))
    {
        return true;
    }

    return false;
}

Piece* Pawn::copy(Board* board) const
{
    return new Pawn(board, this->row, this->col, this->black, true);
}