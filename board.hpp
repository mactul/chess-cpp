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

    /**
     * @brief Get the piece at position `row` `col`
     *
     */
    Piece* get_piece(uint8_t row, uint8_t col) const;

    /**
     * @brief Set the piece pointer at position `row` `col`  
     * @brief If another piece is at this place, it's overwrite.
     * 
     * @param row
     * @param col 
     * @param piece a pointer to an allocated piece.
     * @return true if the row/col is in the board, else false.
     */
    bool set_piece(uint8_t row, uint8_t col, Piece* piece);

    /**
     * @brief Display the whole board in colors in the terminal.
     * 
     */
    void display(void) const;

    /**
     * @brief Display the ending string of the game which is all the piece in the board (whoami representation) followed by the `winner` string.
     * 
     * @param winner A string which is either "?-?", "1-0", "0-1" or "1/2-1/2" representing the winner of the game (white-black)
     */
    void display_csv(const char* winner) const;

    /**
     * @brief Returns whether or not the king is controlled by another piece.
     * 
     * @param black true for getting information about the black king, false for the white king.
     */
    bool is_king_in_chess(bool black) const;

    /**
     * @brief Returns whether or not the player can do something.  
     * @brief If this is true, it's either a stalemate or a checkmate depending of the value of `is_king_in_chess` method.
     * 
     * @param black true to get information about the black player, false for the white player.
     */
    bool no_movements_allowed(bool black);

    /**
     * @brief This method is used by pieces/pawn.cpp to know if a pawn has moved from row-1,col -> row+1,col just before.  
     * @brief In other words, if there is a pawn to eat at position row,col.
     * 
     * @param row
     * @param col 
     * @param black if true, the method looks for a black pawn to eat, if false, it looks for a white pawn to eat.
     */
    bool is_en_passant(uint8_t row, uint8_t col, bool black);

    /**
     * @brief This method is called each time a pawn makes a 2 squares travel.  
     * @brief After each round, this method should be called with row=-1 and col=-1 to disable the en-passant for precedent moves.
     * 
     * @param row should be the middle between the starting and the ending point of the 2 squares move.
     * @param col the column of the move.
     * @param black true if it's a black piece that is moving, false for a white piece.
     * @return `true` if row/col is either negative or in the board.  
     * @return `false` if row/col is outside the board.
     */
    bool set_en_passant(int8_t row, int8_t col, bool black);

    /**
     * @brief Perform a kingside castling move.  
     * @brief Castling is the only movement that move 2 pieces, so it seems more logical to do it by the board.
     * 
     * @param black true to perform a black kingside castling, false for a white kingside castling.
     * @return true if the castling is authorized and was performed.  
     * @return false if the castling is unauthorized.
     */
    bool kingside_castling(bool black);

    /**
     * @brief Perform a queenside castling move.  
     * @brief Castling is the only movement that move 2 pieces, so it seems more logical to do it by the board.
     * 
     * @param black true to perform a black queenside castling, false for a white queenside castling.
     * @return true if the castling is authorized and was performed.  
     * @return false if the castling is unauthorized.
     */
    bool queenside_castling(bool black);
};


/**
 * @brief Convert a row in algebraic notation (1~8) to his equivalent index in the board array.
 * 
 * @param c the character of the notation, between '1' and '8'.
 * @return - a number between 0 and 7 if it succeeded
 * @return - `-1` if `c` was not between '1' and '8'.
 * 
 * @note It's the opposite of `row_index_to_notation`.
 */
int8_t notation_to_row_index(char c);

/**
 * @brief Convert a col in algebraic notation (A~H) to his equivalent index in the board array.
 * 
 * @param c the character of the notation, between 'A' and 'H'.
 * @return - a number between 0 and 7 if it succeeded
 * @return - `-1` if `c` was not between 'A' and 'H'.
 * 
 * @note It's the opposite of `col_index_to_notation`.
 */
int8_t notation_to_col_index(char c);

/**
 * @brief Convert a row index to his equivalent in algebraic notation (1~8).
 * 
 * @param row the index of the row between 0 to 7.
 * @return - a char between '1' and '8' if it succeeded.
 * @return - `-1` if `row` was not between 0 and 7.
 * 
 * @note It's the opposite of `notation_to_row_index`.
 */
char row_index_to_notation(uint8_t row);

/**
 * @brief Convert a col index to his equivalent in algebraic notation (A~H).
 * 
 * @param col the index of the col between 0 to 7.
 * @return - a char between 'A' and 'H' if it succeeded.
 * @return - `-1` if `col` was not between 0 and 7.
 * 
 * @note It's the opposite of `notation_to_col_index`.
 */
char col_index_to_notation(uint8_t col);