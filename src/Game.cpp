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
}

void Game::print_game_board(){
    this->game_board_pointer->print_board();
    return;
    }

int Game::run_game(){

    std::shared_ptr< std::vector<char> > player_tokens_pointer = std::make_shared< std::vector<char> >();

    game_board_pointer = std::make_shared<Board>(board_height, board_width, player_tokens_pointer, run_needed, number_of_players);

    std::shared_ptr<HumanPlayer> player1 = std::make_shared<HumanPlayer>(game_board_pointer, 0);
    player1->set_token('x');
    player_tokens_pointer->push_back('x');

    std::shared_ptr<BotPlayer> player2 = std::make_shared<BotPlayer>(game_board_pointer, 1);
    player2->set_token('o');
    player_tokens_pointer->push_back('o');

    this->player_array[0] = player1;
    this->player_array[1] = player2;

    player1->set_opponent_token();
    player2->set_opponent_token();

    game_board_pointer->all_board_update_runs();
    game_board_pointer->update_board_value();

    bool game_won = false;
    bool game_drawn = false;

    int column_choice = 99;
    int token_position = 99;

    int turn_count = 0;
    int player_number = 99;

    this->game_board_pointer->print_board();

    while (!game_won && !game_drawn){

        for (auto player : player_array){

        turn_count++;

        player_number = (turn_count - 1) % number_of_players;

        column_choice = player->get_move();

        token_position = this->game_board_pointer->make_move(player_tokens_pointer->at(player_number), column_choice);

        this->game_board_pointer->print_board();
        int readable_column = column_choice + 1;
        std::cout << "The last move was: "<< readable_column << std::endl;

        game_won = game_board_pointer->check_for_win( player_tokens_pointer->at(player_number), token_position);
        if(game_won){
            return turn_count;}

        game_drawn = game_board_pointer->check_for_draw();
        if(game_drawn){
            return turn_count;}
        }
    }
return -1;
}
