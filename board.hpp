#pragma once

#define BOARD_SIZE 8

#include <stdint.h>
#include "color_display.hpp"
#include "piece.hpp"

class Piece;

class Board {
private:
    Piece* _board[BOARD_SIZE][BOARD_SIZE] = {{0}};
    uint8_t black_king_row = 0;
    uint8_t black_king_col = BOARD_SIZE-4;
    uint8_t white_king_row = BOARD_SIZE-1;
    uint8_t white_king_col = BOARD_SIZE-4;

    int8_t black_en_passant_row = -1;
    int8_t black_en_passant_col = -1;
    int8_t white_en_passant_row = -1;
    int8_t white_en_passant_col = -1;


    bool display_square(uint8_t row, uint8_t col) const;

    bool is_piece_controlled(uint8_t piece_row, uint8_t piece_col, bool piece_black) const;

public:
    Board();
    ~Board();
    Board(const Board& copy);
    Piece* get_piece(uint8_t row, uint8_t col) const;
    bool set_piece(uint8_t row, uint8_t col, Piece* piece);
    void display(void) const;
    void display_csv(const char* winner) const;

    bool is_king_in_chess(bool black) const;

    bool no_movements_allowed(bool black);

    bool is_en_passant(uint8_t row, uint8_t col, bool black);
    bool set_en_passant(int8_t row, int8_t col, bool black);

    bool kingside_castling(bool black);
    bool queenside_castling(bool black);
};



int8_t notation_to_row_index(char c);
int8_t notation_to_col_index(char c);
char row_index_to_notation(uint8_t row);
char col_index_to_notation(uint8_t col);