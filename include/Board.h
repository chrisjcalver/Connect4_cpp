#ifndef BOARD_H
#define BOARD_H

#include <array>
#include <iostream>
#include <vector>


class Board{

    class Board_Position{

        friend Board;

        protected:
        char token = ' ';
        //{right runs, up runs, up_left, up_right}

        //default fill with zeros
        std::array<std::array<int, 4>, 2> potential_run_count = { { {0,0,0,0}, {0,0,0,0} } };
    };

    int board_height = 0;
    int board_width = 0;

    int run_needed = 0;

    int number_of_players = 99;

    std::vector<char>* token_vector_pointer;

    int number_of_positions = board_height * board_width;

    Board_Position board[42];

    bool check_for_horizontal_win(char player_token, int original_position, int run_needed);

    bool check_for_vertical_win(char player_token, int original_position, int run_needed);

    bool check_for_up_left_win(char player_token, int original_position, int run_needed);

    bool check_for_up_right_win(char player_token, int original_position, int run_needed);

    int single_position_update_right_runs(int player_identifier, char player_token, int position, int run_needed);

    int single_position_update_up_runs(int player_identifier, char player_token, int position, int run_needed);

    int single_position_update_up_left_runs(int player_identifier, char player_token, int position, int run_needed);

    int single_position_update_up_right_runs(int player_identifier, char player_token, int position, int run_needed);

    void single_position_update_runs_count(int position);



    public:

        Board( std::vector<char>* given_token_vector_pointer, int given_run_needed, int number_of_player);


        Board(int height, int width, std::vector<char>* token_vector_pointer, int run_needed);

        //std::array<board_position, 42> get_board_array() {return board_array;}



        int get_board_width() {return this->board_width;}

        char get_token(int position) { return this->board[position].token; }

        int make_move( int player_number, int column);

        bool check_column_is_full(int column_choice);

        bool check_for_draw();

        bool check_for_win(char player_number, int original_position);

        std::array<int,4> get_runs_counts( int position, int player_number){ return board[position].potential_run_count[player_number];}

        void update_affected_positions_runs_counts( int position);

        void update_all_runs();

        void print_board();

};

#endif
