#pragma once

#include "piece.hpp"


class Pawn: public Piece {
private:
    bool no_promotion;  // This boolean disable the promotion if set to true.
                        // Especially, it's disabled for copied pieces because we don't want a copied piece to ask for a promotion and a promotion doesn't affect whether the king of the promoted color is endanger or not.
public:
    Pawn(Board* board, uint8_t row, uint8_t col, bool black, bool no_promotion = false);

    bool move(uint8_t row, uint8_t col, bool fake = false) override;

    const char* display(void) const override;

    const char* whoami(void) const override;

    Piece* copy(Board* board) const override;
};
