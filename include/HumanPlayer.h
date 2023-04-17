#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "Player.h"
#include "Board.h"

#include <iostream>
#include <memory>

class HumanPlayer : public Player

{

public:
    HumanPlayer(std::shared_ptr<Board> game_board_pointer, int player_number) : Player(game_board_pointer, player_number){

        //std::cout << "Human Player initialized" << std::endl;
    }

    int get_move() override;

};

#endif
