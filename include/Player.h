#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
//#include "BotPlayer.h"
//#include "HumanPlayer.h"

class Player{



    protected:

        char token;

        Player(){
        std::cout << "Player is initialised" << std::endl;
        };

    public:

        char get_token(){return token;}

        void set_token(char new_token){
            this->token = new_token;
            return;}

        virtual int get_move(int board_width) const = 0;

};

#endif
