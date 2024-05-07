/**
 * @file piece.hpp
 * @brief This file contains all the method for the abstract class representing a piece.  
 * @brief The most important method of this file is `move_no_geometry`. With this method, we can move a piece regardless of the geometry of the movement but ensuring that every other aspect of the move is legal. In particular, a move that makes the king in chess is illegal.

 * @brief The method `Piece.move` is defined as a virtual method and precisely defined for each type of piece in the `pieces` folder.
 * @brief This method move the piece only if the movement is entirely legal.
 * 
 */

#pragma once

#include <stdint.h>
#include "board.hpp"


class Board;

class Piece {
protected:
    Board* board;  // each piece has a pointer to their board, like that they can see other pieces.
    uint8_t row;   // they also have row and col parameters so they know where they can find themselves on the board.
    uint8_t col;   // the difficulty is to keep this synchronized with the board, that's why it's crucial to use Piece's methods to move a piece.
    bool black;

    bool _has_moved = false;

    /**
     * @brief Move a piece regardless of the geometry of the movement but ensuring that every other aspect of the move is legal.
     * @brief In particular, a move that makes the king in chess is illegal.
     * 
     * @param row the destination row of the move
     * @param col the destination col of the move
     * @param fake if true, then the function act like a const method and only returns whether or not the move is legal.
     * @return `true` if the move is legal  
     * @return `false` if the move is illegal
     */
    bool move_no_geometry(uint8_t row, uint8_t col, bool fake = false);

    /**
     * @brief This returns whether or not the move respects the geometry of a rook move.
     * 
     * @param row the destination row of the move
     * @param col the destination col of the move
     * @return `true` if the move respects the geometry
     * @return `false` if not
     * 
     * @note This is in this file because it's used by the Rook and the Queen
     */
    bool rook_restriction(uint8_t row, uint8_t col) const;

    /**
     * @brief This returns whether or not the move respects the geometry of a Bishop move.
     * 
     * @param row the destination row of the move
     * @param col the destination col of the move
     * @return `true` if the move respects the geometry
     * @return `false` if not
     * 
     * @note This is in this file because it's used by the Bishop and the Queen
     */
    bool bishop_restriction(uint8_t row, uint8_t col) const;

public:
    Piece(Board* board, uint8_t row, uint8_t col, bool black);
    virtual ~Piece();
    bool is_black() const;

    bool has_moved(void) const;

    /**
     * @brief Move a piece regardless of it's a legal move or not as long as the piece doesn't land outside the board or on a piece the same color.  
     * @brief Ensure that every duplicated data between Board/Piece stays coherent and each eaten Piece is deleted in memory.
     * 
     * @param row the destination row of the move
     * @param col the destination col of the move
     * @return `true` if the piece was successfully moved.
     */
    bool unrestricted_move(uint8_t row, uint8_t col);  // this unfortunately has to be public because it's used by the Board class for castling.

    virtual bool move(uint8_t row, uint8_t col, bool fake = false) = 0;
    virtual const char* display(void) const = 0;
    virtual const char* whoami(void) const = 0;

    virtual Piece* copy(Board* board) const = 0;
};