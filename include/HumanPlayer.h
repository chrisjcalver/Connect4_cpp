#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "Player.h"

class HumanPlayer : public Player
{

    char Player::token = 'o';
    void ignoreLine();

public:
    HumanPlayer(){ Player::token = 'o'; };
    int get_move(int board_width);

};

#endif
