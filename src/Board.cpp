#include "Board.h"
#include <iostream>


//constructor

//constructor
Board::Board(){
    Board::board_width = 7;
    Board::board_height = 6;
    //Board_Position game_board[42];
    std::cout << "board initialized"  <<std::endl;
};

Board::Board(int height, int width){

    const int board_height = height;
    const int board_width = width;

    const int number_of_positions = board_height * board_width;

    Board_Position game_board[42];

};



// functions

void Board::print_board(){

    //std::cout << '|' << game_board[this->board_width].get_token() << '|';


    std::cout << "printing board" << std::endl;

    int starting_position = 0;

    for (int y = this->board_height; y >= 1; y--){

        int start_of_row_number = (y - 1) * this->board_width;

        std::cout << '|';

        for (int x = 0; x < this->board_width; x++){

            int board_position_location = start_of_row_number + x;
            std::cout << game_board[board_position_location].get_token() << '|';
        }

        std::cout << std::endl;

    }

    return;
}


