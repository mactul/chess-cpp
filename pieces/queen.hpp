#pragma once

#include "piece.hpp"

class Queen: public Piece {
public:
    Queen(Board* board, uint8_t row, uint8_t col, bool black);

    bool move(uint8_t row, uint8_t col, bool fake = false) override;

    const char* display(void) const override;

    const char* whoami(void) const override;

    Piece* copy(Board* board) const override;
};