#pragma once

#include "board.hpp"

/**
 * @brief Clear the history of the board stored.  
 * @brief This function must be used when the board can never came back to a precedent configuration.
 */
void board_history_reset();

/**
 * @brief Add the actual `board` configuration to the board history list
 * 
 * @param board the actual board which will be copied in a compacted form
 * @return true if the board configuration was added.  
 * @return false if `board` is the third occurrence in the history list.
 */
bool board_history_add(const Board& board);