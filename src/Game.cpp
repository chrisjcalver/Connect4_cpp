#include "Game.h"
#include "Player.h"
#include "BotPlayer.h"
#include "HumanPlayer.h"
#include "Board.h"


Game::Game(){
        //default initialisation


    BotPlayer player1{};

    BotPlayer player2{};


    this->player_vector.push_back(&player2);
    this->player_vector.push_back(&player1);

    this->player_tokens.push_back('x');
    this->player_tokens.push_back('o');


    std::cout<<"game initialized"<< std::endl;

}

Game::~Game()
{
    for (int i = 0; i < player_count; i++)
    {
        delete player_vector[i];
    }
    player_vector.clear();
}


void Game::print_game_board(){
    std::cout << "trying to print board"<<std::endl;
    this->game_board.print_board();
    return;
    }

void Game::run_game(){
    int board_width = this->game_board.get_board_width();
    std::cout << "running game with board width" << board_width << std::endl;
    Game::print_game_board();

    player_vector[0]->set_token('x');
    player_vector[1]->set_token('o');

    std::cout << player_vector[0]->get_token() << std::endl;
    std::cout << player_vector[1]->get_token() << std::endl;
    std::cout << "working this far3" << std::endl;


    std::cout << player_tokens[0]<< std::endl;
    std::cout << player_tokens[1]<< std::endl;




    std::cout << "tokens set up" << std::endl;

    //char player1_token = player_vector[0]->get_token();
    //char player2_token = player_vector[1]->get_token();

    //std::cout << "Player one token is" << player1_token;

    //Create dictionary to avoid calling get_token() every time

    bool game_won = false;

    while (!game_won){

        for( int player_number = 0; player_number < player_count; player_number++ ){

            bool valid_move = false;
            int player_move = 99;
            while(!valid_move){
                std::cout << "working to here";
                std::cout << player_vector[player_number]->get_token();
                player_move = player_vector[player_number]->get_move(board_width);
                std::cout << player_move << std::endl;
                if( this->game_board.get_token(player_move) != ' '){
                    std::cout << "Sorry, that column is full. Please make another choice." << std::endl;
                    break;
                }
                valid_move = true;
                this->game_board.make_move(player_tokens[player_number], player_move);
                this->game_board.print_board();
            }

            std::cout << player_tokens[player_number];
            std::cout << player_move;
            std::cout << run_needed;

            //game_won = game_board.check_for_win( player_tokens[player_number], player_move, run_needed);

        }
    }
    return;
}
