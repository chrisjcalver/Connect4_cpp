#ifndef BOARD_H
#define BOARD_H

#include <array>
#include <iostream>
#include <vector>
#include <memory>


class Board{

    class Board_Position{

        friend Board;

        protected:
        char token = ' ';
        //{right runs, up runs, up_left, up_right, total_value}
        std::array<std::array<int, 5>, 2> potential_run_counts_and_value = { { {0,0,0,0,0}, {0,0,0,0,0} } };

    };

    int board_height;
    int board_width;
    int number_of_positions = 0;

    int run_value_factor = 10;
    std::array<int, 2> board_values = {0,0};

    std::shared_ptr< std::vector<char> > token_vector_pointer;

    int run_needed = 0;

    int number_of_players = 99;

    Board_Position board[42];

    bool check_for_horizontal_win(char player_token, int original_position);

    bool check_for_vertical_win(char player_token, int original_position);

    bool check_for_up_left_win(char player_token, int original_position);

    bool check_for_up_right_win(char player_token, int original_position);

    int single_position_update_right_runs(int player_identifier, char player_token, int position);

    int single_position_update_up_runs(int player_identifier, char player_token, int position);

    int single_position_update_up_left_runs(int player_identifier, char player_token, int positiond);

    int single_position_update_up_right_runs(int player_identifier, char player_token, int position);

    void single_position_update_runs_count(int position);




    public:

        Board(int board_height, int board_width, std::shared_ptr< std::vector<char> > given_token_vector_pointer, int given_run_needed, int number_of_player);

        Board(){};

        char get_player_token( int player_number){ return token_vector_pointer->at(player_number);}

        int get_board_width() {return this->board_width;}

        char get_token(int position) { return this->board[position].token; }

        int make_move( char token, int column);

        void undo_move(int column);

        bool check_column_is_full(int column_choice);

        bool check_for_draw();

        bool check_for_win(char player_token, int original_position);

        std::array<int,5> get_runs_counts( int position, int player_number){ return board[position].potential_run_counts_and_value[player_number];}

        void update_affected_positions_runs_counts( int position);

        void all_board_update_runs();

        void update_board_value();

        void print_board();

        std::array<int,2> get_board_values(){ return board_values;}

        int get_player_board_values(int player_number){ return board_values[player_number];}

        void update_single_player_board_value(int player_number);

};

#endif
