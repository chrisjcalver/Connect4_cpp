#ifndef BOT_PLAYER_H
#define BOT_PLAYER_H

#include "Player.h"
#include "Board.h"

class BotPlayer : public Player
{

    //char token;

public:

    BotPlayer(Board* game_board_pointer, int player_number) : Player( game_board_pointer , player_number){

        std::cout << "Bot Player initialized" << std::endl;
        //std::cout << game_board_pointer->get_board_width << std::endl;
        std::cout << this->board_width << std::endl;

        };


    int get_move() const override;
};

#endif
