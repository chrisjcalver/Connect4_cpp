#ifndef BOARD_H
#define BOARD_H

#include <array>
#include <iostream>


class Board{

    class Board_Position{
        char token = ' ';
        int player1_value = 0;
        int player2_value = 0;

        public:

            //Board_Position(){ std::cout << "board position initialized" << std::endl;}

            char get_token(){ return token;}

            int get_player1_value(){ return player1_value;}

            int get_player2_value(){ return player2_value;}

            void set_token(char new_token){
                token = new_token;
                return;}

    };




    int board_height = 0;
    int board_width = 0;

    int number_of_positions;

    Board_Position board[42];



    public:

        Board();


        Board(int height, int width);

        //std::array<board_position, 42> get_board_array() {return board_array;}



        int get_board_width() {return this->board_width;}

        char get_token(int position) { return this->board[position].get_token(); }

        int make_move( char token, int column);

        bool check_for_horizontal_win(char player_token, int original_position, int run_needed);

        bool check_for_vertical_win(char player_token, int original_position, int run_needed);

        bool check_for_up_left_win(char player_token, int original_position, int run_needed);

        bool check_for_up_right_win(char player_token, int original_position, int run_needed);

        bool check_for_win(char player_token, int original_position, int run_needed);

        void print_board();

};

#endif
