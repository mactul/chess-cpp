#pragma once

#include "piece.hpp"


class Pawn: public Piece {
private:
    bool no_promotion;
public:
    Pawn(Board* board, uint8_t row, uint8_t col, bool black, bool no_promotion = false);

    bool move(uint8_t row, uint8_t col, bool fake = false) override;

    const char* display(void) const override;

    const char* whoami(void) const override;

    bool has_possible_movements(void) const override;

    Piece* copy(Board* board) const override;
};
