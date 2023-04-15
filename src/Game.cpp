#include "Game.h"
#include "Player.h"
#include "BotPlayer.h"
#include "HumanPlayer.h"
#include "Board.h"


Game::Game(){
        //default initialisation


    //BotPlayer player1{};

    //HumanPlayer player2{};


    this->player_vector.push_back(&player1);
    this->player_vector.push_back(&player2);

    this->player_tokens.push_back('x');
    this->player_tokens.push_back('o');


    std::cout<<"game initialized"<< std::endl;

}
/*
Game::~Game()
{
    for (int i = 0; i < player_count; i++)
    {
        delete player_vector[i];
    }
    player_vector.clear();
}
*/
void Game::print_game_board(){
    std::cout << "trying to print board"<<std::endl;
    this->game_board.print_board();
    return;
    }
/*
void Game::run_game(){
    int board_width = this->game_board.get_board_width();
    std::cout << "running game with board width" << board_width << std::endl;
    Game::print_game_board();

    player_vector[0]->set_token('x');
    player_vector[1]->set_token('o');

    char token_check1 = player_vector[0]->get_token();
    //char token_check2 = player_vector[1]->get_token();
    std::cout << "player_vector token to check is: " << token_check1 <<std::endl;
    std::cout << "player1 token to check is: " << player1.get_token() <<std::endl;

            bool valid_move = false;
            int player_move = 99;
            while(!valid_move){
                std::cout << "player1 token is: " << player1.get_token()  << std::endl;
                player_move = player1.get_move(board_width);
                std::cout << player_move << std::endl;
                if( this->game_board.get_token(player_move) != ' '){
                    std::cout << "Sorry, that column is full. Please make another choice." << std::endl;
                    break;
                }
                valid_move = true;
                this->game_board.make_move(player_vector[0]->get_token(), player_move);
                this->game_board.print_board();
            }

            bool game_won = game_board.check_for_win( player_vector[0]->get_token(), player_move, run_needed);


            valid_move = false;
            player_move = 99;
            while(!valid_move){
                std::cout << player2.get_token();
                player_move = player2.get_move(board_width);
                std::cout << player_move << std::endl;
                if( this->game_board.get_token(player_move) != ' '){
                    std::cout << "Sorry, that column is full. Please make another choice." << std::endl;
                    break;
                }
                valid_move = true;
                this->game_board.make_move(player_vector[1]->get_token(), player_move);
                this->game_board.print_board();
            }

            game_won = game_board.check_for_win( player_vector[1]->get_token(), player_move, run_needed);



    return;
    }
*/
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
    bool game_drawn = false;

    int column_choice = 99;
    int token_position = 99;

    int turn_count = 0;
    int player_number = 99;

    while (!game_won && !game_drawn){

        turn_count++;
        player_number = (turn_count - 1) % player_count;

        bool valid_move = false;

        while(!valid_move){
            column_choice = player_vector[player_number]->get_move(board_width);
            if( this->game_board.check_column_is_full(column_choice) == true){
                std::cout << "Sorry, that column is full. Please make another choice." << std::endl;
                break;
            }
            valid_move = true;
            token_position = this->game_board.make_move(player_tokens[player_number], column_choice);
                this->game_board.print_board();
            }

            //std::cout << player_tokens[player_number];
            //std::cout << player_move;
            //std::cout << run_needed;

            game_won = game_board.check_for_win( player_tokens[player_number], token_position, run_needed);
            game_drawn = game_board.check_for_draw();
        }
    return;
}
