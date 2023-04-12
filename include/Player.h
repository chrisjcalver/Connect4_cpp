#ifndef PLAYER_H
#define PLAYER_H


class Player{

    protected:


        char token;

    public:

        Player();

        char get_token(){return token;}
        int get_move();

};

#endif
