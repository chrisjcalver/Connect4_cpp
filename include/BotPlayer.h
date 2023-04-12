#ifndef BOT_PLAYER_H
#define BOT_PLAYER_H

#include "Player.h"

class BotPlayer : public Player
{

    char Player::token = 'x';

public:

    BotPlayer(){ Player::token = 'x'; };

    int get_move();
};

#endif
