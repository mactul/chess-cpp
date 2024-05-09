#include <stdint.h>
#include <vector>
#include "board_history.hpp"

enum PIECES_IDS {
    PIECE_ID_NONE,
    PIECE_ID_KING,
    PIECE_ID_QUEEN,
    PIECE_ID_ROOK,
    PIECE_ID_BISHOP,
    PIECE_ID_KNIGHT,
    PIECE_ID_PAWN
};

typedef struct _compact_piece {
    enum PIECES_IDS piece1_id : 3;
    bool piece1_black         : 1;

    enum PIECES_IDS piece2_id : 3;
    bool piece2_black         : 1;
} __attribute__((packed)) CompactPiece;

typedef struct _compact_board {
    CompactPiece pieces[BOARD_SIZE * BOARD_SIZE / 2];
} CompactBoard;

static std::vector<CompactBoard> _previous_boards;

enum PIECES_IDS get_piece_id(const Piece* piece)
{
    if(piece == nullptr)
    {
        return PIECE_ID_NONE;
    }
    switch(piece->whoami()[1])
    {
        case 'K':
            return PIECE_ID_KING;
        case 'Q':
            return PIECE_ID_QUEEN;
        case 'R':
            return PIECE_ID_ROOK;
        case 'B':
            return PIECE_ID_BISHOP;
        case 'N':
            return PIECE_ID_KNIGHT;
        case 'P':
            return PIECE_ID_PAWN;
        default:
            return PIECE_ID_NONE;  // this should not happen.
    }
}


static bool compact_board_equals(const CompactBoard* cb1, const CompactBoard* cb2)
{
    uint64_t* data1 = (uint64_t*) cb1;
    uint64_t* data2 = (uint64_t*) cb2;

    for(uint8_t i = 0; i < BOARD_SIZE / 2; i++)
    {
        if(data1[i] != data2[i])
        {
            return false;
        }
    }
    return true;
}

static void compact_board_create(const Board& board, CompactBoard* compact_board)
{
    for(uint8_t row = 0; row < BOARD_SIZE; row++)
    {
        for(uint8_t col = 0; col < BOARD_SIZE-1; col += 2)
        {
            CompactPiece compact_piece;
            Piece* piece1 = board.get_piece(row, col);
            Piece* piece2 = board.get_piece(row, col+1);

            compact_piece.piece1_id = get_piece_id(piece1);
            compact_piece.piece2_id = get_piece_id(piece2);

            if(piece1 == nullptr || !piece1->is_black())
            {
                compact_piece.piece1_black = false;
            }
            else
            {
                compact_piece.piece1_black = true;
            }

            if(piece2 == nullptr || !piece2->is_black())
            {
                compact_piece.piece2_black = false;
            }
            else
            {
                compact_piece.piece2_black = true;
            }

            compact_board->pieces[row * BOARD_SIZE / 2 + col / 2] = compact_piece;
        }
    }
}

uint8_t count_board_occurrences(const CompactBoard& compact_board)
{
    uint8_t occ = 0;
    for(CompactBoard& compact_board_stored : _previous_boards)
    {
        if(compact_board_equals(&compact_board_stored, &compact_board))
        {
            occ++;
        }
    }
    return occ;
}


void board_history_reset()
{
    _previous_boards.clear();
}

bool board_history_add(const Board& board)
{
    CompactBoard compact_board;

    compact_board_create(board, &compact_board);

    if(count_board_occurrences(compact_board) >= 2)
    {
        return false;  // stalemate
    }

    _previous_boards.push_back(compact_board);

    return true;
}
