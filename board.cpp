#include "board.hpp"
#include "pieces.hpp"

#include <iostream>


Board::Board()
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        this->_board[1][i] = new Pawn(this, 1, i, true);

        this->_board[BOARD_SIZE-2][i] = new Pawn(this, BOARD_SIZE-2, i, false);
    }

    for(int i = 0; i <= 1; i++)
    {
        int row = i * (BOARD_SIZE-1);

        this->_board[row][0]            = new Rook(this, row, 0, !i);
        this->_board[row][BOARD_SIZE-1] = new Rook(this, row, BOARD_SIZE-1, !i);

        this->_board[row][1]            = new Knight(this, row, 1, !i);
        this->_board[row][BOARD_SIZE-2] = new Knight(this, row, BOARD_SIZE-2, !i);

        this->_board[row][2]            = new Bishop(this, row, 2, !i);
        this->_board[row][BOARD_SIZE-3] = new Bishop(this, row, BOARD_SIZE-3, !i);

        this->_board[row][3]            = new Queen(this, row, 3, !i);

        this->_board[row][BOARD_SIZE-4] = new King(this, row, BOARD_SIZE-4, !i);
    }
}

Board::Board(const Board& copy): black_king_row(copy.black_king_row), black_king_col(copy.black_king_col), white_king_row(copy.white_king_row), white_king_col(copy.white_king_col), black_en_passant_row(copy.black_en_passant_row), black_en_passant_col(copy.black_en_passant_col), white_en_passant_row(copy.white_en_passant_row), white_en_passant_col(copy.white_en_passant_col)
{
    for(uint8_t row = 0; row < BOARD_SIZE; row++)
    {
        for(uint8_t col = 0; col < BOARD_SIZE; col++)
        {
            if(copy._board[row][col] == nullptr)
            {
                this->_board[row][col] = nullptr;
            }
            else
            {
                this->_board[row][col] = copy._board[row][col]->copy(this);
            }
        }
    }
}

Board::~Board()
{
    for(uint8_t row = 0; row < BOARD_SIZE; row++)
    {
        for(uint8_t col = 0; col < BOARD_SIZE; col++)
        {
            delete this->_board[row][col];
        }
    }
}

Piece* Board::get_piece(uint8_t row, uint8_t col) const
{
    if(row >= BOARD_SIZE || col >= BOARD_SIZE)
    {
        return nullptr;
    }
    return this->_board[row][col];
}

bool Board::set_piece(uint8_t row, uint8_t col, Piece* piece)
{
    if(row >= BOARD_SIZE || col >= BOARD_SIZE)
    {
        return false;
    }
    if(piece != nullptr)
    {
        delete _board[row][col];  // We only delete the piece if it was taken by another

        const char* name = piece->whoami();
        if(name[1] == 'K')
        {
            if(name[0] == 'w')
            {
                this->white_king_row = row;
                this->white_king_col = col;
            }
            else
            {
                this->black_king_row = row;
                this->black_king_col = col;
            }
        }
    }
    this->_board[row][col] = piece;

    
    return true;
}

bool Board::display_square(uint8_t row, uint8_t col) const
{
    if(row >= BOARD_SIZE || col >= BOARD_SIZE)
    {
        return false;
    }

    if(((row + col) & 1) == 0)
    {
        // white background
        if(this->_board[row][col] == nullptr)
        {
            print_in_color(" ", COLOR_BLACK_ON_WHITE);
        }
        else
        {
            #ifdef ONLY_ASCII
                if(this->_board[row][col]->is_black())
                {
                    print_in_color(this->_board[row][col]->display(), COLOR_BLACK_ON_WHITE);
                }
                else
                {
                    print_in_color(this->_board[row][col]->display(), COLOR_GREY_ON_WHITE);
                }
            #else
                print_in_color(this->_board[row][col]->display(), COLOR_BLACK_ON_WHITE);
            #endif
        }
    }
    else
    {
        // black background
        if(this->_board[row][col] == nullptr)
        {
            print_in_color(" ", COLOR_BLACK_ON_GREEN);
        }
        else
        {
            #ifdef ONLY_ASCII
                if(this->_board[row][col]->is_black())
                {
                    print_in_color(this->_board[row][col]->display(), COLOR_BLACK_ON_GREEN);
                }
                else
                {
                    print_in_color(this->_board[row][col]->display(), COLOR_GREY_ON_GREEN);
                }
            #else
                print_in_color(this->_board[row][col]->display(), COLOR_BLACK_ON_GREEN);
            #endif
        }
    }
    return true;
}


void Board::display(void) const
{
    std::cout << "  ";
    for(int col = 0; col < BOARD_SIZE; col++)
    {
        std::cout << " " << col_index_to_notation(col) << " ";
    }
    std::cout << "\n";
    for(int row = 0; row < BOARD_SIZE; row++)
    {
        std::cout << row_index_to_notation(row) << " ";
        for(int col = 0; col < BOARD_SIZE; col++)
        {
            this->display_square(row, col);
        }
        std::cout << " " << row_index_to_notation(row) << "\n";
    }
    std::cout << "  ";
    for(int col = 0; col < BOARD_SIZE; col++)
    {
        std::cout << " " << col_index_to_notation(col) << " ";
    }
    std::cout << std::endl;
}

void Board::display_csv(const char* winner) const
{
    for(int row = BOARD_SIZE-1; row >= 0; row--)
    {
        for(int col = 0; col < BOARD_SIZE; col++)
        {
            if(this->_board[row][col] != nullptr)
            {
                std::cout << this->_board[row][col]->whoami();
            }
            std::cout << ",";
        }
    }
    std::cout << " " << winner << std::endl;
}

bool Board::is_piece_controlled(uint8_t piece_row, uint8_t piece_col, bool piece_black) const
{
    for(int row = 0; row < BOARD_SIZE; row++)
    {
        for(int col = 0; col < BOARD_SIZE; col++)
        {
            if(this->_board[row][col] != nullptr && (piece_black ^ this->_board[row][col]->is_black()) && this->_board[row][col]->move(piece_row, piece_col, true))
            {
                return true;
            }
        }
    }
    return false;
}

bool Board::is_king_in_chess(bool black) const
{
    return is_piece_controlled(black ? this->black_king_row: this->white_king_row, black ? this->black_king_col: this->white_king_col, black);
}


static bool piece_can_move(Piece* piece)
{
    for(int row = 0; row < BOARD_SIZE; row++)
    {
        for(int col = 0; col < BOARD_SIZE; col++)
        {
            if(piece->move(row, col, true))
            {
                return true;
            }
        }
    }
    return false;
}

bool Board::no_movements_allowed(bool black)
{
    for(int row = 0; row < BOARD_SIZE; row++)
    {
        for(int col = 0; col < BOARD_SIZE; col++)
        {
            if(this->_board[row][col] != nullptr && this->_board[row][col]->is_black() == black && piece_can_move(this->_board[row][col]))
            {
                return false;
            }
        }
    }
    return true;
}

bool Board::is_en_passant(uint8_t row, uint8_t col, bool black)
{
    if(this->black_en_passant_row < 0 || this->black_en_passant_col < 0)
    {
        return false;
    }
    if(black)
    {
        return this->black_en_passant_row == row && this->black_en_passant_col == col;
    }
    return this->white_en_passant_row == row && this->white_en_passant_col == col;
}

bool Board::set_en_passant(int8_t row, int8_t col, bool black)
{
    if(row >= BOARD_SIZE || col >= BOARD_SIZE)
    {
        return false;
    }
    if(black)
    {
        this->black_en_passant_row = row;
        this->black_en_passant_col = col;
    }
    else
    {
        this->white_en_passant_row = row;
        this->white_en_passant_col = col;
    }

    return true;
}


bool Board::kingside_castling(bool black)
{
    uint8_t king_row = black ? 0: BOARD_SIZE-1;
    char color = black ? 'b': 'w';
    Piece* piece_king = this->_board[king_row][BOARD_SIZE-4];
    Piece* piece_rook = this->_board[king_row][BOARD_SIZE-1];

    if(piece_king == nullptr || piece_king->has_moved() || piece_king->whoami()[1] != 'K'  || piece_king->whoami()[0] != color)
    {
        return false;
    }

    if(piece_rook == nullptr || piece_rook->has_moved() || piece_rook->whoami()[1] != 'R'  || piece_rook->whoami()[0] != color)
    {
        return false;
    }

    for(uint8_t col = BOARD_SIZE-3; col < BOARD_SIZE-1; col++)
    {
        if(this->_board[king_row][col] != nullptr)
        {
            return false;
        }
        if(this->is_piece_controlled(king_row, col, black))
        {
            return false;
        }
    }

    (void)piece_king->unrestricted_move(king_row, BOARD_SIZE-2);
    (void)piece_rook->unrestricted_move(king_row, BOARD_SIZE-3);


    return true;
}

bool Board::queenside_castling(bool black)
{
    uint8_t king_row = black ? 0: BOARD_SIZE-1;
    char color = black ? 'b': 'w';
    Piece* piece_king = this->_board[king_row][BOARD_SIZE-4];
    Piece* piece_rook = this->_board[king_row][0];

    if(piece_king == nullptr || piece_king->has_moved() || piece_king->whoami()[1] != 'K'  || piece_king->whoami()[0] != color)
    {
        return false;
    }

    if(piece_rook == nullptr || piece_rook->has_moved() || piece_rook->whoami()[1] != 'R'  || piece_rook->whoami()[0] != color)
    {
        return false;
    }

    if(this->_board[king_row][1] != nullptr)
    {
        return false;
    }

    for(uint8_t col = 2; col < BOARD_SIZE-4; col++)
    {
        if(this->_board[king_row][col] != nullptr)
        {
            return false;
        }
        if(this->is_piece_controlled(king_row, col, black))
        {
            return false;
        }
    }

    (void)piece_king->unrestricted_move(king_row, 2);
    (void)piece_rook->unrestricted_move(king_row, 3);


    return true;
}


char row_index_to_notation(uint8_t row)
{
    if(row >= BOARD_SIZE)
    {
        return -1;
    }
    return '8' - row;
}


int8_t notation_to_row_index(char c)
{
    if(c < '1' || c > '8')
    {
        return -1;
    }
    return '8' - c;
}

char col_index_to_notation(uint8_t col)
{
    if(col >= BOARD_SIZE)
    {
        return -1;
    }
    return 'A' + col;
}

int8_t notation_to_col_index(char c)
{
    if(c >= 'A' && c <= 'H')
    {
        c += 'a' - 'A';
    }
    if(c < 'a' || c > 'h')
    {
        return -1;
    }
    return c - 'a';
}