#pragma once

#include "piece.hpp"

class Rook: public Piece {
public:
    Rook(Board* board, uint8_t row, uint8_t col, bool black);

    bool move(uint8_t row, uint8_t col, bool fake = false) override;

    const char* display(void) const override;

    const char* whoami(void) const override;

    MovementMap list_maybe_possible_movements() const override;

    Piece* copy(Board* board) const override;
};