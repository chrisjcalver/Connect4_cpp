#include "Game.h"
#include "Player.h"
#include "BotPlayer.h"
#include "HumanPlayer.h"
#include "Board.h"

#include <vector>
#include <memory>

Game::Game(){

    run_needed = 4;

    number_of_players = 2;

    board_height = 6;

    board_width = 7;



    //game_board_pointer = &game_board;



    //HumanPlayer player2{};




    //std::cout<<"game initialized"<< std::endl;

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
    //std::cout << "trying to print board"<<std::endl;
    this->game_board_pointer->print_board();
    return;
    }

void Game::run_game(){

    std::shared_ptr< std::vector<char> > player_tokens_pointer = std::make_shared< std::vector<char> >();

    game_board_pointer = std::make_shared<Board>(board_height, board_width, player_tokens_pointer, run_needed, number_of_players);

    //game_board_pointer = new Board(board_height, board_width, &player_tokens, run_needed, number_of_players);

    //BotPlayer player1(game_board_pointer, 0);

    //auto player_tokens_pointer = std::make_shared<std::vector<uint8_t> >(player_tokens);

    //player_tokens = std::make_shared<std::vector<char>>;

    std::shared_ptr<BotPlayer> player1 = std::make_shared<BotPlayer>(game_board_pointer, 0);

    player1->set_token('x');

    player_tokens_pointer->push_back('x');



    std::shared_ptr<BotPlayer> player2 = std::make_shared<BotPlayer>(game_board_pointer, 1);

    //BotPlayer player2(game_board_pointer, 1);

    player2->set_token('o');

    player_tokens_pointer->push_back('o');

    //layer* player_one_add = &player1;

    this->player_array[0] = player1;

    this->player_array[1] = player2;

    player1->set_opponent_token();

    player2->set_opponent_token();

    //player_array[0]->set_token('x');

    //Player* test_player = player_array[0];

    //char token_to_test = player_array[0]->get_token();

    //this->player_vector.push_back(&player2);
    //player_array[1]->set_token('o');

    //Player* test_player = player_vector[0];



    int board_width = this->game_board_pointer->get_board_width();
    //std::cout << "running game with board width" << board_width << std::endl;





    game_board_pointer->all_board_update_runs();
    game_board_pointer->update_board_value();

    //print_game_board();

    //std::cout << player_array[0]->get_token() << std::endl;
    //std::cout << player_vector[1]->get_token() << std::endl;
    //std::cout << "working this far3" << std::endl;


    //std::cout << player_tokens[0]<< std::endl;
    //std::cout << player_tokens[1]<< std::endl;




    //std::cout << "tokens set up" << std::endl;

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

    //std::cout << "Working here 4" << std::endl;



    while (!game_won && !game_drawn){

        for (auto player : player_array){

        //std::cout << "Working here 5" << std::endl;

        turn_count++;

        //std::cout << "turn number: " << turn_count << std::endl;

        //std::cout << number_of_players << std::endl;

        player_number = (turn_count - 1) % number_of_players;


        //std::cout << player_number << std::endl;

        bool valid_move = false;

        //std::cout << "Working here 1" << std::endl;

        while(!valid_move){
          //  std::cout << "Working here 2" << std::endl;
            //std::cout << player_number << std::endl;
            //std::cout << player_array[0]->get_token() << std::endl;
            //std::cout << player_array[1]->get_token() << std::endl;
           // std::cout << "player number is: " << player_number;
            //std::cout << "Working here 5" << std::endl;
            //std::cout << player->get_token();
            //std::cout << "Working here 6" << std::endl;
            column_choice = player->get_move();
            //std::cout << column_choice << std::endl;
            if( this->game_board_pointer->check_column_is_full(column_choice) == true){
                std::cout << "Sorry, that column is full. Please make another choice." << std::endl;
                continue;
            }
            //std::cout << "Working here 5" << std::endl;
            valid_move = true;
            //Updating board run_counts occurs within this function
            //std::cout << player_tokens[player_number] << std::endl;
            //std::cout << column_choice << std::endl;
            token_position = this->game_board_pointer->make_move(player_tokens_pointer->at(player_number), column_choice);
            //this->game_board_pointer->print_board();
            int readable_column = column_choice + 1;
            //std::cout << "The last move was: "<< readable_column << std::endl;
            }

            //std::cout << player_tokens[player_number];
            //std::cout << player_move;
            //std::cout << run_needed;

            //std::cout << "checking for win at: " <<  token_position << "for: " << player_tokens[player_number];
            game_won = game_board_pointer->check_for_win( player_tokens_pointer->at(player_number), token_position);
            if(game_won){
                return;}

            game_drawn = game_board_pointer->check_for_draw();
            if(game_drawn){
                return;}
        }
        }

    return;
}
