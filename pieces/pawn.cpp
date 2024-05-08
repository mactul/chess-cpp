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


static void promote(Board* board, uint8_t row, uint8_t col, bool black)
{
    char answer[20];
    char piece_type = 0;
    std::cout << "Promotion ! ";
    while(piece_type != 'Q' && piece_type != 'R' && piece_type != 'B' && piece_type != 'N')
    {
        std::cout << "To which piece do you want to promote your pawn ? (Q, R, B, N): " << std::flush;
        if(std::fgets(answer, 20, stdin) == nullptr)
        {
            // their is no data left to read, this should not happen.
            std::cerr << "Fatal error, data corrupted" << std::endl;
            std::exit(1);
        }
        piece_type = answer[0];
    }

    Piece* piece;
    switch(piece_type)
    {
        case 'Q':
            piece = new Queen(board, row, col, black);
            break;
        case 'R':
            piece = new Rook(board, row, col, black);
            break;
        case 'B':
            piece = new Bishop(board, row, col, black);
            break;
        case 'N':
            piece = new Knight(board, row, col, black);
            break;
        default:
            std::cerr << "Fatal error, the impossible happened" << std::endl;
            std::exit(1);
    }
    board->set_piece(row, col, piece);  // this act a like eating the pawn with the new piece created, but their is no white/black verification.
}

bool Pawn::move(uint8_t row, uint8_t col, bool fake)
{
    // NOTE:
    // Because we are using unsigned integers, we shouldn't perform comparisons like `a-1 == b`.
    // Instead we perform the comparison `a == b+1`.
    // Especially, `row == this->row+1` significate that the new row is bigger by 1 unit and `row+1 == this->row` significate that the new row is smaller by 1 unit.
    //
    // One could ask why using unsigned integers: this is because it makes much easier to verify that a move is in the board, we don't have to verify that row and col are greater than 0.

    if(this->black)
    {
        // The pawn is black: 3 possibilities:
        // - if the pawn has moved:
        //     - it can only move 1 row to the bottom and optionally 1 col to the left or the right.
        // - if the pawn hasn't moved:
        //     - if it move 1 col to the left or the right, it can only move 1 row to the bottom.
        //     - if it doesn't move to the left or the right, it can move 1 or 2 row to the bottom.
        if((this->_has_moved && this->row+1 != row) || (!this->_has_moved && this->row+1 != row && (this->row+2 != row || this->col != col)))
        {
            return false;
        }
    }
    else
    {
        // The pawn is white: 3 possibilities:
        // - if the pawn has moved:
        //     - it can only move 1 row to the top and optionally 1 col to the left or the right.
        // - if the pawn hasn't moved:
        //     - if it move 1 col to the left or the right, it can only move 1 row to the top.
        //     - if it doesn't move to the left or the right, it can move 1 or 2 row to the top.
        if((this->_has_moved && this->row != row+1) || (!this->_has_moved && this->row != row+1 && (this->row != row+2 || this->col != col)))
        {
            return false;
        }
    }

    if(col == this->col)
    {
        // This is a linear move, it can't eat a piece.
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
        // this is a diagonal move, it MUST eat a piece.
        Piece* piece = this->board->get_piece(row, col);
        if(piece == nullptr || piece->is_black() == this->black)
        {
            // the destination of the move is not a piece, if it's not an en-passant, that's an error.
            if(!this->board->is_en_passant(row, col, !this->black))
            {
                return false;
            }
            if(!fake)
            {
                // a fake move must not eat the pawn en-passant.
                this->board->set_piece(row + (!this->black ? 1: -1), col, nullptr);
            }
        }
    }
    else
    {
        return false;
    }

    if(fake)
    {
        // Even if their is a promotion, this will not change either the king is in danger or not.
        // We keep the promotion only for real movements.
        return this->move_no_geometry(row, col, true);
    }

    // We have to calculate this before moving the piece since this->row will take the value of row.
    bool two_squares_move = false;
    if(this->row == row+2 || this->row+2 == row)
    {
        two_squares_move = true;
    }

    if(!this->move_no_geometry(row, col))
    {
        return false;
    }

    if(two_squares_move)
    {
        this->board->set_en_passant(this->row + (this->black ? -1: 1), this->col, this->black);
    }

    if(!this->no_promotion && ((this->black && row == BOARD_SIZE-1) || (!this->black && row == 0)))
    {
        promote(this->board, this->row, this->col, this->black);
    }
    return true;
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


Piece* Pawn::copy(Board* board) const
{
    return new Pawn(board, this->row, this->col, this->black, true);
}