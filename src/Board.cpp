#include "Board.h"
#include <iostream>

//constructor
Board::Board(std::vector<char>* given_token_vector_pointer, int given_run_needed, int given_number_of_players)
    : token_vector_pointer{given_token_vector_pointer}, run_needed{given_run_needed}, number_of_players{given_number_of_players}
{
    this->board_width = 7;
    this->board_height = 6;
    //Board_Position game_board[42];
    std::cout << "board initialized"  <<std::endl;
};

Board::Board(int height, int width, std::vector<char>* token_vector_pointer, int run_needed){

    const int board_height = height;
    const int board_width = width;

    const int number_of_positions = board_height * board_width;

    //Board_Position game_board[42];

};



// functions

void Board::print_board(){

    //The board is a 1D array representation of 2D board. game_board[0] is top left of what would be the 2D array


    std::cout << "printing board" << std::endl;

    for (int y = 0; y < this->board_height; y++){

        int start_of_row_number = y * this->board_width;

        std::cout << '|';

        for (int x = 0; x < this->board_width; x++){

            int board_position_location = start_of_row_number + x;
            std::cout << board[board_position_location].token << '|';
        }

        std::cout << std::endl;

    }

    return;
}

int Board::make_move(int player_number, int column){

    char player_token = token_vector_pointer->at(player_number);
    int position_to_check = (this->board_height - 1) * this->board_width + column;
    bool position_occupied = true;

    //the test to see if column is full is already included in the Game class run_game()
    while (position_occupied){
        if (board[position_to_check].token == ' ')
            {
            position_occupied = false;
            board[position_to_check].token = player_token;
            return position_to_check;
            }
        position_to_check = position_to_check - this->board_width;
    }
return position_to_check;
}

bool Board::check_column_is_full( int column_choice){
    std::cout << "checking column" << column_choice << std::endl;
    bool column_full = false;
    //Top row starts from zero so checking the position that is same as column_choice will check for top row
    std::cout << "token is" << this->board[column_choice].token << std::endl;
    if( this->board[column_choice].token != ' '){
        column_full = true;
    }
    return column_full;
}

bool Board::check_for_draw(){
    bool draw = true;
    bool column_full;
    for (int column = 0; column < this->board_width; column++){
        column_full = this->check_column_is_full(column);
        if (!column_full) {
            draw = false;
            return draw;}
    }
    return draw;
}

//Four directions to check: Horizontal (Check Right), Vertical (Check Up), Diagonal UpLeft (Check UpLeft) and Diagonal UpRight (Check UpRight)
//Attempt to get N in z row always counting right and/or up. Out of bounds check right and up.
//Loop N times in opposite direction of check to ensure have covered all possible wins. Out of bounds check left and down

//Out of bounds: upper: position < 0; lower: position > height*width - 1;
//               left: position % board_width > original_position % board_width; right: position % board_width > original_position % board_width

bool Board::check_for_horizontal_win(char player_token, int original_position, int run_needed){
    bool has_won_bool = false;
    int starting_position = 99;
    int position = 98;
    std::cout << "checking horizontal win";
    //This loop moves the starting position left in order to count right
    for (int count_back = 0; count_back < run_needed; count_back ++){

        //Decrease by one each time move left
        starting_position = original_position - count_back;
        //Check out of bounds left
        if (starting_position % this->board_width > original_position % this->board_width)
                {
                return has_won_bool;
                }

        int run_count = 0;

        // This loop checks for runs to the right
        for (int count_forward = 0; count_forward < run_needed; count_forward ++){

            // Position increases by 1 as moving to the right
            position = starting_position + count_forward;

            //Check out of bounds right
            if (position % this->board_width < original_position % this->board_width)
                {
                break;
                }

            if (this->board[position].token != player_token)
                {
                break;
                }

                run_count++;

                if( run_count == run_needed)
                {
                    has_won_bool = true;
                    return has_won_bool;
                }
            }
        //std::cout << std::endl;
    }
    return has_won_bool;
}



bool Board::check_for_vertical_win(char player_token, int original_position, int run_needed){
    bool has_won_bool = false;
    int starting_position = 99;
    int position = 98;

    std::cout << "checking vertical win";
    // This loop moves the starting position down
    for (int count_back = 0; count_back < run_needed; count_back ++){
        // Moving down a row adds the board_width to the position
        starting_position = original_position + board_width*count_back;
        //Check out of bounds down (as the start steps down to check to up)
        if (starting_position > this->board_height*this->board_width - 1)
                {
                //further checks will also be out of bounds
                return has_won_bool;
                }

        int run_count = 0;

        // This loop checks for runs moving upwards
        for (int count_forward = 0; count_forward < run_needed; count_forward ++){

            //Moving up decreases the position by the board_width
            position = starting_position - count_forward*board_width;

            //Check out of bounds upper
            if (position < 0)
                {
                break;
                }

            if (this->board[position].token != player_token)
                {
                break;
                }

                run_count++;

                if( run_count == run_needed)
                {
                    has_won_bool = true;
                    return has_won_bool;
                }
            }
        //std::cout << std::endl;
    }
    return has_won_bool;
}

bool Board::check_for_up_left_win(char player_token, int original_position, int run_needed){
    bool has_won_bool = false;
    int starting_position = 99;
    int position = 98;
    // Loop to progressively move down and right before checking up left
    for (int count_back = 0; count_back < run_needed; count_back ++){

        //increase increments of board_width + 1 as moving down adds board_width to the position and moving right adds 1.

        starting_position = original_position + count_back*(this->board_width + 1);

        // Check out of bounds down or right
        if (starting_position > this->board_height*this->board_width - 1 || position % this->board_width < original_position % this->board_width)
                {
                return has_won_bool;
                }

        int run_count = 0;
        for (int count_forward = 0; count_forward < run_needed; count_forward ++){

            // counting up and left. decrease by board_width + 1 each time. Decrease by board_width for going up, then going left decreases another 1
            position = starting_position - count_forward * (this->board_width - 1);
            //std::cout << position << " ";

            //Check out of bounds up or left
            if (position < 0 || starting_position % this->board_width > original_position % this->board_width)
                {
                break;
                }

            if (this->board[position].token != player_token)
                {
                break;
                }

                run_count++;

                if( run_count == run_needed)
                {
                    has_won_bool = true;
                    return has_won_bool;
                }
            }
        //std::cout << std::endl;
    }
    return has_won_bool;
}

bool Board::check_for_up_right_win(char player_token, int original_position, int run_needed){
    bool has_won_bool = false;
    int starting_position = 99;
    int position = 98;

    //initital loop goes down and left before checking up right runs.
    for (int count_back = 0; count_back < run_needed; count_back ++){

        //increments of (board_width - 1). down row increases by board_width, then going left decreases by 1.
        starting_position = original_position + count_back*(this->board_width - 1);
        //Check out of bounds down or left
        if (starting_position > this->board_height*this->board_width - 1 || starting_position % this->board_width > original_position % this->board_width)
                {
                return has_won_bool;
                }

        int run_count = 0;
        //This loop checks for runs up and right
        for (int count_forward = 0; count_forward < run_needed; count_forward ++){

            //decrements of (board_width - 1). up row decreases position by board_width, going right increases by 1.
            position = starting_position - count_forward*(board_width - 1);
            //std::cout << position << " ";

            //Check out of bounds up or right
                if (position < 0 || position % this->board_width < original_position % this->board_width)
                {
                break;
                }

            if (this->board[position].token != player_token)
                {
                break;
                }

                run_count++;

                if( run_count == run_needed)
                {
                    has_won_bool = true;
                    return has_won_bool;
                }
            }
        //std::cout << std::endl;
    }
    return has_won_bool;
}

bool Board::check_for_win(char player_token, int original_position){

    std::cout << "checking for win" << std::endl;
    bool has_won_bool = false;

    has_won_bool = check_for_horizontal_win(player_token, original_position, run_needed);

    if (has_won_bool == true){ return has_won_bool;}

    has_won_bool = check_for_vertical_win(player_token, original_position, run_needed);

    if (has_won_bool == true){ return has_won_bool;}

    has_won_bool = check_for_up_left_win(player_token, original_position, run_needed);

    if (has_won_bool == true){ return has_won_bool;}

    has_won_bool = check_for_up_right_win(player_token, original_position, run_needed);

    if (has_won_bool == true){ return has_won_bool;}

    return has_won_bool;
}

//right runs are position 0 in the potential runs array
int Board::single_position_update_right_runs(int player_identifier, char player_token, int starting_position, int run_needed){

    int further_position_to_check = 99;
    int potential_run = 0;

    // If a run is impossible due to it being blocked it will always be blocked
    if(this->board[starting_position].potential_run_count[player_identifier][0] == 9){ return 9;}

    // This loop checks for runs to the right
    for (int count_forward = 0; count_forward < run_needed; count_forward ++){

        // Position increases by 1 as moving to the right
        further_position_to_check = starting_position + count_forward;

        //Check out of bounds right. If it goes out of bounds it will never be a winning run so return 9.
        if (further_position_to_check % this->board_width < starting_position % this->board_width)
            {
            this->board[starting_position].potential_run_count[player_identifier][0] = 9;
            return 9;
        }
        //If a board position is filled with opponents token that winning run will never be possible
        if (this->board[further_position_to_check].token != player_token && this->board[further_position_to_check].token != player_token)
            {
            this->board[starting_position].potential_run_count[player_identifier][0] = 9;
            return 9;
        }

        if (this->board[further_position_to_check].token == player_token)
            {
            potential_run++;
        }
    }

this->board[starting_position].potential_run_count[player_identifier][0] = 9;
return potential_run;
}

//Up runs are position [1] in potential_runs array
int Board::single_position_update_up_runs(int player_identifier, char player_token, int starting_position, int run_needed){

    int further_position_to_check = 99;
    int potential_run = 0;

    // If a run is impossible due to it being blocked it will always be blocked
    if(this->board[starting_position].potential_run_count[player_identifier][1] == 9){ return 9;}

    // This loop checks for potential runs up
    for (int count_forward = 0; count_forward < run_needed; count_forward ++){

        // Position decreases by board width as moving up
        further_position_to_check = starting_position - count_forward*this->board_width;

        //Check out of bounds up. If it goes out of bounds it will never be a winning run so return 9.
        if (further_position_to_check < 0)
            {
            this->board[starting_position].potential_run_count[player_identifier][1] = 9;
            return 9;
        }
        //If a board position is filled with opponents token that winning run will never be possible
        if (this->board[further_position_to_check].token != player_token && this->board[further_position_to_check].token != player_token)
            {
            this->board[starting_position].potential_run_count[player_identifier][1] = 9;
            return 9;
        }

        if (this->board[further_position_to_check].token == player_token)
            {
            potential_run++;
        }
    }

this->board[starting_position].potential_run_count[player_identifier][1] = potential_run;
return potential_run;
}

//Up Left are position [2] in potential_runs array
int Board::single_position_update_up_left_runs(int player_identifier, char player_token, int starting_position, int run_needed){
    //This variable should always be updated before being used
    int further_position_to_check = 99;
    int potential_run = 0;

    // If a run is impossible due to it being blocked it will always be blocked
    if(this->board[starting_position].potential_run_count[player_identifier][2] == 9){ return 9;}

    // This loop checks for potential runs up left
    for (int count_forward = 0; count_forward < run_needed; count_forward ++){

        // Position decreases in increments of (board width + 1) as moving up decreases by board width and moving left decreases by 1
        further_position_to_check = starting_position - count_forward*this->board_width;

        //Check out of bounds up or left. If it goes out of bounds it will never be a winning run so return 9.
        if (further_position_to_check < 0 || further_position_to_check % this->board_width > starting_position % this->board_width)
            {
            this->board[starting_position].potential_run_count[player_identifier][2] = 9;
            return 9;
        }
        //If a board position is filled with opponents token that winning run will never be possible
        if (this->board[further_position_to_check].token != player_token && this->board[further_position_to_check].token != player_token)
            {
            this->board[starting_position].potential_run_count[player_identifier][2] = 9;
            return 9;
        }

        if (this->board[further_position_to_check].token == player_token)
            {
            potential_run++;
        }
    }
this->board[starting_position].potential_run_count[player_identifier][2] = potential_run;
return potential_run;
}

//Up Right runs are position [3] in potential_runs array
int Board::single_position_update_up_right_runs(int player_identifier, char player_token, int starting_position, int run_needed){

    //This variable should always be updated before being used
    int further_position_to_check = 99;
    int potential_run = 0;

    // If a run is impossible due to it being blocked it will always be blocked
    if(this->board[starting_position].potential_run_count[player_identifier][3] == 9){ return 9;}

    // This loop checks for potential runs up left
    for (int count_forward = 0; count_forward < run_needed; count_forward ++){

        // Position decreases in increments of (board width - 1) as moving up decreases by board width and moving right increases by 1
        further_position_to_check = starting_position - count_forward*this->board_width;

        //Check out of bounds up or right. If it goes out of bounds it will never be a winning run so return 9.
        if (further_position_to_check < 0 || further_position_to_check % this->board_width < starting_position % this->board_width)
            {
            this->board[starting_position].potential_run_count[player_identifier][3] = 9;
            return 9;
        }
        //If a board position is filled with opponents token that winning run will never be possible
        if (this->board[further_position_to_check].token != player_token && this->board[further_position_to_check].token != player_token)
            {
            this->board[starting_position].potential_run_count[player_identifier][3] = 9;
            return 9;
        }

        if (this->board[further_position_to_check].token == player_token)
            {
            potential_run++;
        }
    }
this->board[starting_position].potential_run_count[player_identifier][3] = potential_run;
return potential_run;
}

void Board::single_position_update_runs_count(int position){

    char player_token = '$';

    for (int player_number = 0; player_number <= number_of_players; player_number++){

        player_token = token_vector_pointer->at(player_number);

        //for( int position = 0; position < this->number_of_positions; position++){

            single_position_update_right_runs(player_number, player_token, position, run_needed);

            single_position_update_up_runs(player_number, player_token, position, run_needed);

            single_position_update_up_left_runs(player_number, player_token, position, run_needed);

            single_position_update_up_right_runs(player_number, player_token, position, run_needed);
        }
    return;
}

//void Board::all_board_update_all_runs();
