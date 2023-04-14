#ifndef PLAYER_H
#define PLAYER_H

//#include "BotPlayer.h"
//#include "HumanPlayer.h"

class Player{

    char token = '$';

    protected:

        Player(){

        };

    public:

        char get_token(){return token;}

        void set_token(char new_token){
            this->token = new_token;
            return;}

        virtual int get_move(int board_width) const = 0;

};

#endif
