#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "Player.h"

class HumanPlayer : public Player
{

    //char Player::token = 'o';
    //void ignoreLine() const;

public:
    HumanPlayer(){ std::cout << "Human Player initialized" << std::endl;};
    int get_move(int board_width) const override;

};

#endif
