#include "Game.h"
#include "Player.h"
#include "BotPlayer.h"
#include "HumanPlayer.h"
#include "Board.h"


Game::Game(){
        //default initialisation

    BotPlayer player1{};

    HumanPlayer player2{};

    std::cout<<"game initialized"<< std::endl;

}



void Game::print_game_board(){
    std::cout << "trying to print board"<<std::endl;
    this->game_board.print_board();
    return;
    }

void Game::run_game(){
    int board_width = this->game_board.get_board_width();
    std::cout << "running game" << std::endl;
    Game::print_game_board();

    char player1_token = player1.get_token();
    char player2_token = player2.get_token();

    bool game_won = false;
    while (!game_won){

        bool valid_move = false;
        while(!valid_move){

            int player1_move = player1.get_move();
            std::cout << player1_move << std::endl;
            if( this->game_board.get_token(player1_move) != ' '){
                std::cout << "Sorry, that column is full. Please make another choice." << std::endl;
                break;
                }
            valid_move = true;
            this->game_board.make_move(player1_token, player1_move);
            this->game_board.print_board();
        }

        valid_move = false;
        while(!valid_move){
            int player2_move = player2.get_move(board_width);
            std::cout << player2_move << std::endl;
            if(this->game_board.get_token(player2_move) != ' '){
                std::cout << "Sorry, that column is full. Please make another choice." << std::endl;
                break;
                }
            valid_move = true;
            int move_location = this->game_board.make_move(player2_token, player2_move);
            game_won = this->game_board.check_for_win(player2_token, move_location, 4);

            if (game_won){ std::cout << "game won";}

            this->game_board.print_board();
        }



    }
    return;
    }

