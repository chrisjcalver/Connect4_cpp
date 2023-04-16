#include"BotPlayer.h"

#include <iostream>

int BotPlayer::get_move()const {


    int move_position = 99;

    bool this_player_won = false;
    bool opponent_won = false;

    std::array<int, 2> board_values = {0,0};

    int relative_value = -10000;
    int best_relative_value = -10000;
    int best_column = 0;
//
    for(int column_number = 0; column_number < this->board_width; column_number++){

        std::cout << "For column: " << column_number << std::endl;

        if( game_board_pointer->check_column_is_full(column_number) ){
            relative_value = -10000000;
            continue;}

        else{
            move_position = game_board_pointer->make_move(this->token, column_number);


            this_player_won = game_board_pointer->check_for_win(this->token, move_position);
            if (this_player_won){
                game_board_pointer->undo_move(column_number);
                return column_number;
            }
            opponent_won = game_board_pointer->check_for_win('o', move_position);
            if (opponent_won){
                game_board_pointer->undo_move(column_number);
                return column_number;
            }

            board_values = game_board_pointer->get_board_values();

            relative_value = board_values[player_number] - 2*board_values[(player_number + 1) % 2];

            std::cout << "relative value is: " << relative_value <<std::endl;

            if (relative_value > best_relative_value){

                best_column = column_number;
                best_relative_value = relative_value;

                std::cout << "best_column: " << best_column <<std::endl;
                std::cout << "best_relative_value: " << best_relative_value <<std::endl;
            }

            game_board_pointer->undo_move(column_number);
        }

    }
return best_column;
}
