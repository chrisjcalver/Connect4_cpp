#include "Board.h"
#include <iostream>
#include<cmath>
#include<memory>
#include <thread>

//constructor
Board::Board(int given_board_height, int given_board_width, std::shared_ptr< std::vector<char> > given_token_vector_pointer, int given_run_needed, int given_number_of_players)
    : board_height{given_board_height}, board_width{given_board_width}, number_of_positions{given_board_height*given_board_width},
    token_vector_pointer{given_token_vector_pointer}, run_needed{given_run_needed}, number_of_players{given_number_of_players}
{

    //Board_Position game_board[42];
    //std::cout << "board initialized with board_width"  << this->board_width <<std::endl;
};

//Board::Board(int height, int width, std::vector<char>* token_vector_pointer, int run_needed){

    //const int board_height = height;
    //const int board_width = width;

    //const int number_of_positions = board_height * board_width;

    //Board_Position game_board[42];

//};



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
    /*
    std::cout << "position 35 and player 0" << std::endl;
    for (const auto& run_count : get_runs_counts( 35, 0)) {
    std::cout << run_count << ", ";
    }
    std::cout << std::endl;

    std::cout << "position 38 and player 1" << std::endl;
    for (const auto& run_count : get_runs_counts( 38, 1)) {
    std::cout << run_count << ", ";
    }
    std::cout << std::endl;

    std::cout << "position 41 and player 1" << std::endl;
    for (const auto& run_count : get_runs_counts( 41, 1)) {
    std::cout << run_count << ", ";
    }

    std::cout << std::endl;

    //std::cout << "player 1 board value is " << board_values[0] << std::endl;
    //std::cout << "player 2 board value is " << board_values[1] << std::endl;
*/
    return;
}

int Board::make_move(char player_token, int column){

//std::cout << "checking column: " << column << std::endl;
//std::cout << "board width is: " << this->board_width << std::endl;
//std::cout << "board height is: " << this->board_height << std::endl;

    int position_to_check = (this->board_height - 1) * this->board_width + column;
    bool position_occupied = true;

    //the test to see if column is full is already included in the Game class run_game()
    while (position_occupied){

           // std::cout << "checking position: " << position_to_check << std::endl;

        if (board[position_to_check].token == ' ')
            {
            position_occupied = false;
    //std::cout << "Placing token at: " << position_to_check << std::endl;
    //std::cout << "board width is: " << this->board_width << std::endl;
            board[position_to_check].token = player_token;
            //std::cout << "board width is: " << this->board_width << std::endl;
            //std::cout << "Going to check positions affected by " << position_to_check << std::endl;
            this->update_affected_positions_runs_counts(position_to_check);
            //std::cout << "board width is: " << this->board_width << std::endl;
            this->update_board_value();
            //std::cout << "board width is: " << this->board_width << std::endl;
            //std::cout << "board height is: " << this->board_height << std::endl;


            return position_to_check;
            }
        position_to_check = position_to_check - this->board_width;
    }

//this return should never be reached
return 99;
}

void Board::undo_move(int column){
    int position_to_check = column;
    bool position_occupied = false;
    while(!position_occupied && position_to_check < number_of_positions){
        if (board[position_to_check].token != ' '){
            board[position_to_check].token = ' ';
            this->update_affected_positions_runs_counts(position_to_check);
            this->update_board_value();
            return;
        }
        position_to_check = position_to_check + this->board_width;
    }
    return;
}

bool Board::check_column_is_full( int column_choice){
    //std::cout << "checking column" << column_choice << std::endl;
    bool column_full = false;
    //Top row starts from zero so checking the position that is same as column_choice will check for top row
    //std::cout << "token is" << this->board[column_choice].token << std::endl;
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

bool Board::check_for_horizontal_win(char player_token, int original_position){
    bool has_won_bool = false;
    int starting_position = 99;
    int position = 98;
    int run_count = 0;
    //std::cout << "checking horizontal win for original: " << original_position << "for token: " << player_token << std::endl;
    //This loop moves the starting position left in order to count right
    for (int count_back = 0; count_back < run_needed; count_back ++){

        //Decrease by one each time move left
        starting_position = original_position - count_back;
        //std::cout << "starting position is: " << starting_position << std::endl;
        //Check out of bounds left
        if (starting_position % this->board_width > original_position % this->board_width  || (starting_position < 0 ) )
                {
                return has_won_bool;
                }

        run_count = 0;

        // This loop checks for runs to the right
        for (int count_forward = 0; count_forward < run_needed; count_forward ++){

            // Position increases by 1 as moving to the right
            position = starting_position + count_forward;
            //std::cout << "position is: " << position << std::endl;
            //Check out of bounds right
            if (position % this->board_width < starting_position % this->board_width)
                {
                break;
                }

            if (this->board[position].token != player_token)
                {
                break;
                }

                run_count++;
//std::cout << "run_count is: " << run_count << std::endl;
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



bool Board::check_for_vertical_win(char player_token, int original_position){
    bool has_won_bool = false;
    int starting_position = 99;
    int position = 98;

    //std::cout << "checking vertical win";
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

bool Board::check_for_up_left_win(char player_token, int original_position){
    bool has_won_bool = false;
    int starting_position = 99;
    int position_to_check = 99;
    // Loop to progressively move down and right before checking up left
    for (int count_back = 0; count_back < run_needed; count_back ++){

        //increments of board_width + 1 as moving down adds board_width to the position and moving right adds 1.

        starting_position = original_position + count_back*(this->board_width + 1);

        // Check out of bounds down or right
        if (starting_position > this->board_height*this->board_width - 1 || starting_position % this->board_width < original_position % this->board_width)
                {
                return has_won_bool;
                }

        int run_count = 0;
        for (int count_forward = 0; count_forward < run_needed; count_forward ++){

            // decrement of board_width + 1 each time. Decrease by board_width for going up, then going left decreases another 1
            position_to_check = starting_position - count_forward * (this->board_width + 1);
            //std::cout << position << " ";

            //Check out of bounds up or left
            if (position_to_check < 0 || position_to_check % this->board_width > starting_position % this->board_width)
                {
                break;
                }

            if (this->board[position_to_check].token != player_token)
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

bool Board::check_for_up_right_win(char player_token, int original_position){
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
                if (position < 0 || position % this->board_width < starting_position % this->board_width)
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

    //std::cout << "checking for win" << std::endl;
    bool has_won_bool = false;

    has_won_bool = check_for_horizontal_win(player_token, original_position);

    if (has_won_bool == true){ return has_won_bool;}

    has_won_bool = check_for_vertical_win(player_token, original_position);

    if (has_won_bool == true){ return has_won_bool;}

    has_won_bool = check_for_up_left_win(player_token, original_position);

    if (has_won_bool == true){ return has_won_bool;}

    has_won_bool = check_for_up_right_win(player_token, original_position);

    if (has_won_bool == true){ return has_won_bool;}

    return has_won_bool;
}

//{right runs, up runs, up_left, up_right}

//right runs are position 0 in the potential runs array
int Board::single_position_update_right_runs(int player_identifier, char player_token, int starting_position){

    int further_position_to_check = 99;
    int potential_run = 0;

    // If a run is impossible due to it being blocked it will always be blocked
    //if(this->board[starting_position].potential_run_counts_and_value[player_identifier][0] == 9){ return 9;}

    // This loop checks for runs to the right
    for (int count_forward = 0; count_forward < run_needed; count_forward ++){

        // Position increases by 1 as moving to the right
        further_position_to_check = starting_position + count_forward;

        //Check out of bounds right. If it goes out of bounds it will never be a winning run so return 9.
        if (further_position_to_check % this->board_width < starting_position % this->board_width )
            {
            this->board[starting_position].potential_run_counts_and_value[player_identifier][0] = 9;
            return 9;
        }
        //If a board position is filled with opponents token that winning run will never be possible
        if (this->board[further_position_to_check].token != player_token && this->board[further_position_to_check].token != ' ')
            {
            this->board[starting_position].potential_run_counts_and_value[player_identifier][0] = 9;
            return 9;
        }

        if (this->board[further_position_to_check].token == player_token)
            {
            potential_run++;
        }
    }

this->board[starting_position].potential_run_counts_and_value[player_identifier][0] = potential_run;
return potential_run;
}

//Up runs are position [1] in potential_runs array
int Board::single_position_update_up_runs(int player_identifier, char player_token, int starting_position){

    int further_position_to_check = 99;
    int potential_run = 0;

    //std::cout << "Checking " << starting_position << std::endl;2
    //std::cout << "for token " << player_token << std::endl;

    // If a run is impossible due to it being blocked it will always be blocked
    //if(this->board[starting_position].potential_run_counts_and_value[player_identifier][1] == 9){ return 9;}

    // This loop checks for potential runs up
    for (int count_forward = 0; count_forward < run_needed; count_forward ++){

        // Position decreases by board width as moving up
        further_position_to_check = starting_position - count_forward*this->board_width;

        //Check out of bounds up. If it goes out of bounds it will never be a winning run so return 9.
        if (further_position_to_check < 0)
            {
            this->board[starting_position].potential_run_counts_and_value[player_identifier][1] = 9;
            return 9;
        }
        //If a board position is filled with opponents token that winning run will never be possible
        if (this->board[further_position_to_check].token != player_token && this->board[further_position_to_check].token != ' ')
            {
            this->board[starting_position].potential_run_counts_and_value[player_identifier][1] = 9;
            return 9;
        }

        if (this->board[further_position_to_check].token == player_token)
            {
            potential_run++;
        }
    }
//std::cout << "Potential run is" << potential_run <<std::endl;
this->board[starting_position].potential_run_counts_and_value[player_identifier][1] = potential_run;
return potential_run;
}

//Up Left are position [2] in potential_runs array
int Board::single_position_update_up_left_runs(int player_identifier, char player_token, int starting_position){
    //This variable should always be updated before being used
    int further_position_to_check = 99;
    int potential_run = 0;

    // If a run is impossible due to it being blocked it will always be blocked
    //if(this->board[starting_position].potential_run_counts_and_value[player_identifier][2] == 9){ return 9;}

    // This loop checks for potential runs up left
    for (int count_forward = 0; count_forward < run_needed; count_forward ++){

        // Decrements of (board width + 1) as moving up decreases by board width and moving left decreases by 1
        further_position_to_check = starting_position - count_forward*(this->board_width + 1);

        //Check out of bounds up or left. If it goes out of bounds it will never be a winning run so return 9.
        if (further_position_to_check < 0 || further_position_to_check % this->board_width > starting_position % this->board_width)
            {
            this->board[starting_position].potential_run_counts_and_value[player_identifier][2] = 9;
            return 9;
        }
        //If a board position is filled with opponents token that winning run will never be possible
        if (this->board[further_position_to_check].token != player_token && this->board[further_position_to_check].token != ' ')
            {
            this->board[starting_position].potential_run_counts_and_value[player_identifier][2] = 9;
            return 9;
        }

        if (this->board[further_position_to_check].token == player_token)
            {
            potential_run++;
        }
    }
this->board[starting_position].potential_run_counts_and_value[player_identifier][2] = potential_run;
return potential_run;
}

//Up Right runs are position [3] in potential_runs array
int Board::single_position_update_up_right_runs(int player_identifier, char player_token, int starting_position){

    //This variable should always be updated before being used
    int further_position_to_check = 99;
    int potential_run = 0;

    // If a run is impossible due to it being blocked it will always be blocked
    //if(this->board[starting_position].potential_run_counts_and_value[player_identifier][3] == 9){ return 9;}

    // This loop checks for potential runs up left
    for (int count_forward = 0; count_forward < run_needed; count_forward ++){

        // Decrements of (board width - 1) as moving up decreases by board width and moving right increases by 1
        further_position_to_check = starting_position - count_forward*(this->board_width - 1);

        //Check out of bounds up or right. If it goes out of bounds it will never be a winning run so return 9.
        if (further_position_to_check < 0 || further_position_to_check % this->board_width < starting_position % this->board_width)
            {
            this->board[starting_position].potential_run_counts_and_value[player_identifier][3] = 9;
            return 9;
        }
        //If a board position is filled with opponents token that winning run will never be possible
        if (this->board[further_position_to_check].token != player_token && this->board[further_position_to_check].token != ' ')
            {
            this->board[starting_position].potential_run_counts_and_value[player_identifier][3] = 9;
            return 9;
        }

        if (this->board[further_position_to_check].token == player_token)
            {
            potential_run++;
        }
    }
this->board[starting_position].potential_run_counts_and_value[player_identifier][3] = potential_run;
return potential_run;
}

void Board::update_board_value(){

  for (int player_number = 0; player_number < number_of_players; player_number++ ){

    update_single_player_board_value(player_number);
  }

return;
}

void Board::update_single_player_board_value(int player_number){
    int board_value = 0;
        //std::cout << "number of positions is " << number_of_positions;
        for (int position = 0; position < number_of_positions; position++){
            board_value = board_value + this->board[position].potential_run_counts_and_value[player_number][4];
        }

        board_values[player_number] = board_value;
return;
}

void Board::single_position_update_runs_count(int position){
//std::cout << "bw6: " << this->board_width << std::endl;
    char player_token = '$';

    int right_runs = 0;
    int up_runs = 0;
    int up_left_runs = 0;
    int up_right_runs = 0;

    int position_value = 0;

    for (int player_number = 0; player_number < number_of_players; player_number++){

        position_value = 0;
        //std::cout << "starting position value is " << position_value <<std::endl;
        player_token = token_vector_pointer->at(player_number);
        //std::cout << "checking single position " << position << " for " << player_token <<std::endl;

        //for( int position = 0; position < this->number_of_positions; position++){
//std::cout << "bw7: " << this->board_width << std::endl;
            right_runs = single_position_update_right_runs(player_number, player_token, position);
            //std::cout << "right runs are " << right_runs <<std::endl;
            if (right_runs == 9){
                position_value = position_value + 0;
                }
            else{
                position_value = position_value + pow(run_value_factor,right_runs);
            }

            int right_value_to_add = pow(run_value_factor,right_runs);
        //std::cout << "bw8: " << this->board_width << std::endl;
            //std::cout << "so adding " << right_value_to_add <<std::endl;
            up_runs = single_position_update_up_runs(player_number, player_token, position);
//std::cout << "up runs are " << right_runs <<std::endl;
            if (up_runs == 9){
                position_value = position_value + 0;
            }
            else{
                position_value = position_value + pow(run_value_factor,up_runs);
            }
            int up_value_to_add = pow(run_value_factor,up_runs);
            //std::cout << "so adding " << up_value_to_add <<std::endl;
//std::cout << "bw9: " << this->board_width << std::endl;
            up_left_runs = single_position_update_up_left_runs(player_number, player_token, position);

            if (up_left_runs == 9){
                position_value = position_value + 0;
            }
            else{
                position_value = position_value + pow(run_value_factor,up_left_runs);
            }
//std::cout << "bw10: " << this->board_width << std::endl;
            up_right_runs = single_position_update_up_right_runs(player_number, player_token, position);
            if (up_right_runs == 9){
            position_value = position_value + 0;
            }
            else{
            position_value = position_value + pow(run_value_factor,up_right_runs);
            }

        this->board[position].potential_run_counts_and_value[player_number][4] = position_value;
    }

    return;
}

//This function cycles through moving down, left, down right and down left to update these positions as a move may affect their run counts
void Board::update_affected_positions_runs_counts( int original_position){
   // std::cout << "bw1: " << this->board_width << std::endl;
    //std::cout << "Now checking positions affected by " << original_position << std::endl;
    int position_to_check = 99;
    // move right
    for (int count_back = 0; count_back < run_needed; count_back ++){

        // Moving down a row adds the board_width to the position
        position_to_check = original_position + board_width*count_back;
        //std::cout << "Now checking positions affected by " << position_to_check << std::endl;
        //Check out of bounds down (as the start steps down to check to up)
        if (position_to_check > this->board_height*this->board_width - 1)
            {
            //No need to check this position or any further
            break;
            }
            // std::cout << "bw2: " << this->board_width << std::endl;
        this->single_position_update_runs_count(position_to_check);
    }
    //move left
    for (int count_back = 0; count_back < run_needed; count_back ++){

        //Decrease by one each time move left
        position_to_check = original_position - count_back;
        //Check out of bounds left

        int original_position_modulo = original_position % this->board_width;
       // std::cout << "original_position is" << original_position_modulo << std::endl;

                int to_check_modulo = position_to_check % this->board_width;
        //std::cout << "to_check_modulo is" << to_check_modulo << std::endl;

        if ( (position_to_check % this->board_width) > (original_position % this->board_width) || (position_to_check < 0 ) )
            {
            //No need to check this position or any further
            break;
            }
           // std::cout << "bw3: " << this->board_width << std::endl;
            //std::cout << "checking for position: " << position_to_check << std::endl;
        this->single_position_update_runs_count(position_to_check);
    }
        //move down right
    for (int count_back = 0; count_back < run_needed; count_back ++){

        //increase increments of board_width + 1 as moving down adds board_width to the position and moving right adds 1.
        position_to_check = original_position + count_back*(this->board_width + 1);

        // Check out of bounds down or right
        if (position_to_check > (this->board_height*this->board_width - 1) || (position_to_check % this->board_width) < (original_position % this->board_width) )
            {
            //No need to check this position or any further
            break;
            }
        this->single_position_update_runs_count(position_to_check);
    }
    //move down left
    for (int count_back = 0; count_back < run_needed; count_back ++){

    //increments of (board_width - 1). down row increases by board_width, then going left decreases by 1.
    position_to_check = original_position + count_back*(this->board_width - 1);
    //Check out of bounds down or left
    if ( (position_to_check > this->board_height*this->board_width - 1) || (position_to_check % this->board_width) > (original_position % this->board_width) || (position_to_check < 0 ) )
            {
            //No need to check this one or any further
            break;
            }
            //std::cout << "bw4: " << this->board_width << std::endl;
    this->single_position_update_runs_count(position_to_check);
    }

return;
}

void Board::all_board_update_runs(){
    //std::cout << "updating all runs" <<std::endl;
    for (int position = 0; position < number_of_positions; position++){

        single_position_update_runs_count(position);
    }

return;}
