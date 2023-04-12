#ifndef GAME_H
#define GAME_H

#include "Board.h"

#include "Player.h"
#include "BotPlayer.h"
#include "HumanPlayer.h"

class Game
{

private:

    Board game_board;

    BotPlayer player1;

    HumanPlayer player2;

public:

    Game();

    /*
    ~Game(){

        delete game_board;
        delete player1;
        delete player2;

    }
*/


    void print_game_board();

    void run_game();




};

#endif

