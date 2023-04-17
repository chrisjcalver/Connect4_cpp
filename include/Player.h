#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "Board.h"
#include <memory>
class Player{

    protected:

        char token;

        int board_width = 0;

        std::shared_ptr<Board> game_board_pointer;

        int player_number;

        int opponent_number;

        char opponent_token;

        Player(std::shared_ptr<Board> game_board_pointer, int given_player_number) : game_board_pointer{game_board_pointer}, player_number{given_player_number}
        {
        board_width = game_board_pointer->get_board_width();
        opponent_number = (player_number + 1) % 2;
        }

    public:

        char get_token(){return token;}

        void set_token(char new_token){
            this->token = new_token;
            return;}

        char set_opponent_token(){
            opponent_token = this->game_board_pointer->get_player_token( opponent_number);

            return opponent_token;
        }

        virtual int get_move() = 0;

};

#endif
