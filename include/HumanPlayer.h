#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "Player.h"

class HumanPlayer : public Player
{

    char token = 'o';
    void ignoreLine();

public:

    int get_move(int board_width);

};

#endif
