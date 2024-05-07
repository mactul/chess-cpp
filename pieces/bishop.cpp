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


MovementMap Bishop::list_maybe_possible_movements() const
{
    return (MovementMap)(-1);  // all possible movements
}


/*const std::vector<Movement> Bishop::possible_movements(void) const
{
    std::vector<Movement> movements;
    uint8_t top_left_offset = MIN(this->row, this->col);
    uint8_t top_right_offset = MIN(this->row, BOARD_SIZE-1 - this->col);
    uint8_t bottom_left_offset = MIN(BOARD_SIZE-1 - this->row, this->col);
    uint8_t bottom_right_offset = MIN(BOARD_SIZE-1 - this->row, BOARD_SIZE-1 - this->col);

    for(uint8_t i = 1; i <= top_left_offset; i++)
    {
        if(this->fake_unrestricted_move(this->row - i, this->col - i))
        {
            Movement m = {.dest_row = (uint8_t)(this->row - i), .dest_col = (uint8_t)(this->col - i)};
            movements.push_back(m);
        }
    }

    for(uint8_t i = 1; i <= top_right_offset; i++)
    {
        if(this->fake_unrestricted_move(this->row - i, this->col + i))
        {
            Movement m = {.dest_row = (uint8_t)(this->row - i), .dest_col = (uint8_t)(this->col + i)};
            movements.push_back(m);
        }
    }

    for(uint8_t i = 1; i <= bottom_left_offset; i++)
    {
        if(this->fake_unrestricted_move(this->row + i, this->col - i))
        {
            Movement m = {.dest_row = (uint8_t)(this->row + i), .dest_col = (uint8_t)(this->col - i)};
            movements.push_back(m);
        }
    }

    for(uint8_t i = 1; i <= bottom_right_offset; i++)
    {
        if(this->fake_unrestricted_move(this->row + i, this->col + i))
        {
            Movement m = {.dest_row = (uint8_t)(this->row + i), .dest_col = (uint8_t)(this->col + i)};
            movements.push_back(m);
        }
    }

    return movements;
}*/

Piece* Bishop::copy(Board* board) const
{
    return new Bishop(board, this->row, this->col, this->black);
}