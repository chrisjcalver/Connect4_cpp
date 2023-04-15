#ifndef BOT_PLAYER_H
#define BOT_PLAYER_H

#include "Player.h"

class BotPlayer : public Player
{

    //char token;

public:

    BotPlayer(){std::cout << "Bot Player initialized" << std::endl;};

    int get_move(int board_width) const override;
};

#endif
