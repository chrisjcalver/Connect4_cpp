#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "Player.h"
#include "Board.h"

#include <iostream>

class HumanPlayer : public Player
    //char Player::token;
    //void ignoreLine() const;
{
    //int board_width;

public:
    HumanPlayer(Board* game_board_pointer) : Player(game_board_pointer){

        //this->board_width = 3;

        int width_to_print = board_width;

        std::cout << "Human Player initialized" << std::endl;

        //std::cout << game_board_pointer->get_board_width << std::endl;
        std::cout << this->board_width << std::endl;

        std::cout << width_to_print << std::endl;};

    int get_move() const override;

};

#endif
