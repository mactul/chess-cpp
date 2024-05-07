#include <iostream>
#include <cstdio>  // for fgets which make much more sens than `cin >>` to get a string with a fixed max size
#include <cstring>

#include "macros.h"
#include "board.hpp"

#define MAX_COMMAND_SIZE 32

#define IS_O_LIKE_CHAR(c) ((c) == '0' || (c) == 'o' || (c) == 'O')


static bool verbose_king_in_chess(Board& board, bool black_turn)
{

    if(board.is_king_in_chess(black_turn))
    {
        std::cout << (black_turn ? "Black": "White") << " King in chess !\n";

        return true;
    }

    return false;
}


int main()
{
    bool black_turn = false;
    char winner[8] = "?-?";
    Board board = Board();

    board.display();

    while(1)
    {
        Piece* piece = nullptr;
        char command[MAX_COMMAND_SIZE];
        int8_t start_row, end_row, start_col, end_col;
        
        if(verbose_king_in_chess(board, black_turn))
        {
            if(board.is_king_mat(black_turn))
            {
                if(black_turn)
                {
                    winner[0] = '1';
                    winner[2] = '0';
                }
                else
                {
                    winner[0] = '0';
                    winner[2] = '1';
                }
                std::cout << "checkmate !" << std::endl;
                break;
            }
        }

        if(board.no_movements_allowed(black_turn))
        {
            std::strcpy(winner, "1/2-1/2");
            std::cout << "Stalemate !" << std::endl;
            break;
        }

        
        std::cout << "\n";
        print_in_color("", black_turn ? COLOR_WHITE_ON_BLACK: COLOR_BLACK_ON_WHITE);
        std::cout << (black_turn ? " black": " white") << " turn, play with algebraic notation (eg. d2d4): " << std::flush;
        std::fgets(command, MAX_COMMAND_SIZE, stdin);

        if(std::strcmp(command, "/quit\n") == 0)
        {
            break;
        }
        if(std::strcmp(command, "/resign\n") == 0)
        {
            break;
        }
        if(std::strcmp(command, "/draw\n") == 0)
        {
            break;
        }

        if(IS_O_LIKE_CHAR(command[0]) && command[1] == '-' && IS_O_LIKE_CHAR(command[2]) && command[3] == '-' && IS_O_LIKE_CHAR(command[4]))
        {
            // O-O-O
            if(!board.queenside_castling(black_turn))
            {
                std::cerr << "You can't make a queenside castling in this situation." << std::endl;
                continue;
            }
            goto MOVEMENT_END;
        }
        else if(IS_O_LIKE_CHAR(command[0]) && command[1] == '-' && IS_O_LIKE_CHAR(command[2]))
        {
            // O-O
            if(!board.kingside_castling(black_turn))
            {
                std::cerr << "You can't make a kingside castling in this situation." << std::endl;
                continue;
            }
            goto MOVEMENT_END;
        }

        if((start_col = notation_to_col_index(command[0])) == -1
            || (start_row = notation_to_row_index(command[1])) == -1
            || (end_col = notation_to_col_index(command[2])) == -1
            || (end_row = notation_to_row_index(command[3])) == -1)
        {
            std::cerr << "The format is incorrect, please enter a move like d1d2, with d1 the starting position and d2 the final position." << std::endl;
            continue;
        }

        piece = board.get_piece(start_row, start_col);
        if(piece == nullptr || piece->is_black() != black_turn)
        {
            command[2] = '\0';  // to get ride of the destination part.
            std::cerr << "Their is no " << (black_turn ? "black": "white") << " piece at position " << command << std::endl;
            continue;
        }


        {
            Board board_copy = Board(board);

            if(!board_copy.get_piece(start_row, start_col)->move(end_row, end_col))
            {
                std::cerr << "This is an illegal move" << std::endl;
                continue;
            }

            if(board_copy.is_king_in_chess(black_turn))
            {
                std::cerr << "This will kill your King, you can't do that." << std::endl;
                continue;
            }
        }

        if(!piece->move(end_row, end_col))
        {
            std::cerr << "This is an illegal move" << std::endl;
            continue;
        }

MOVEMENT_END:
        std::cout << "\n";
        board.display();


        black_turn = !black_turn;
    }

    std::cout << "\n";

    board.display_csv(winner);

    return 0;
}