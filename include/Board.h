#ifndef BOARD_H
#define BOARD_H

#include <array>
#include <iostream>


class Board{

    class Board_Position{

        friend Board;

        protected:
        char token = ' ';
        //{right runs, up runs, up_left, up_right}

        //default fill with zeros
        int potential_run_count[2][4] = {};

        //int player1_run_count[4] = {0, 0, 0, 0};
        //int player2_run_count[4] = {0, 0, 0, 0};

        public:

            //Board_Position(){ std::cout << "board position initialized" << std::endl;}
 /*
            char get_token(){ return token;}

            //int get_player1_run_count(){ return this->player1_run_count;}

            //int get_player2_run_count(){ return this->player2_run_count;}

            void set_token(char new_token){
                token = new_token;
                return;}

            int get_player1_right_runs(){ return player1_run_count[0]; }

            void set_player1_right_runs(int right_run_count){
            player1_run_count[0] = right_run_count;
            return;
            }

            int get_player1_up_runs(){ return player1_run_count[1]; }

            void set_player1_up_runs(int up_run_count){
            player1_run_count[1] = up_run_count;
            return;
            }

            int get_player1_up_left_runs(){ return player1_run_count[3]; }

            void set_player1_up_left_runs(int up_left_run_count){
            player1_run_count[3] = up_left_run_count;
            return;
            }

            int get_player1_up_right_runs(){ return player1_run_count[4]; }

            void set_player1_up_right_runs(int up_right_run_count){
            player1_run_count[4] = up_right_run_count;
            return;
            }

            int get_player2_right_runs(){ return player2_run_count[0]; }

            void set_player2_right_runs(int right_run_count){
            player2_run_count[0] = right_run_count;
            return;
            }

            int get_player2_up_runs(){ return player2_run_count[1]; }

            void set_player2_up_runs(int up_run_count){
            player2_run_count[1] = up_run_count;
            return;
            }

            int get_player2_up_left_runs(){ return player2_run_count[3]; }

            void set_player2_up_left_runs(int up_left_run_count){
            player2_run_count[3] = up_left_run_count;
            return;
            }

            int get_player2_up_right_runs(){ return player2_run_count[4]; }

            void set_player2_up_right_runs(int up_right_run_count){
            player2_run_count[4] = up_right_run_count;
            return;
            }
            */
    };



    int board_height = 0;
    int board_width = 0;

    int number_of_positions;

    Board_Position board[42];

    bool check_for_horizontal_win(char player_token, int original_position, int run_needed);

    bool check_for_vertical_win(char player_token, int original_position, int run_needed);

    bool check_for_up_left_win(char player_token, int original_position, int run_needed);

    bool check_for_up_right_win(char player_token, int original_position, int run_needed);

    int single_position_update_right_runs(int player_identifier, char player_token, int position, int run_needed);

    int single_position_update_up_runs(int player_identifier, char player_token, int position, int run_needed);

    int single_position_update_up_left_runs(int player_identifier, char player_token, int position, int run_needed);

    int single_position_update_up_right_runs(int player_identifier, char player_token, int position, int run_needed);

    void single_position_update_all_runs(int player_identifier, char player_token, int run_needed);



    public:

        Board();


        Board(int height, int width);

        //std::array<board_position, 42> get_board_array() {return board_array;}



        int get_board_width() {return this->board_width;}

        char get_token(int position) { return this->board[position].token; }

        int make_move( char token, int column);



        bool check_for_win(char player_token, int original_position, int run_needed);

        void all_board_update_all_runs();

        void print_board();

};

#endif
