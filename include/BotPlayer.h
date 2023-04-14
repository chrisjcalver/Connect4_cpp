#ifndef BOT_PLAYER_H
#define BOT_PLAYER_H

#include "Player.h"

class BotPlayer : public Player
{

    //char Player::token = 'x';

public:

    BotPlayer(){};

    int get_move(int board_width) const override;
};

#endif
