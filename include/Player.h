#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "Board.h"
//#include "BotPlayer.h"
//#include "HumanPlayer.h"

class Player{



    protected:

        char token;

        int board_width = 0;

        Board* game_board_pointer;

        Player(Board* given_game_board_pointer) : game_board_pointer{given_game_board_pointer}
        {
        //board_width = 10;
        board_width = game_board_pointer->get_board_width();
        std::cout << "Player is initialised" << std::endl;
        std::cout << "Board_width is" << board_width << std::endl;
        }

    public:

        char get_token(){return token;}

        void set_token(char new_token){
            this->token = new_token;
            return;}

        virtual int get_move() const = 0;

};

#endif
