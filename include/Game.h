#ifndef GAME_H
#define GAME_H

#include "Board.h"

#include "Player.h"

class Game
{

private:

    Board game_board;

    //Player player1;

    //Player player2;

public:

    Game();

    void print_game_board();

    void run_game();



};

#endif

