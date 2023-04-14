#ifndef GAME_H
#define GAME_H

#include <vector>

#include "Board.h"
#include "Player.h"
#include "BotPlayer.h"
#include "HumanPlayer.h"

class Game
{

private:

    Board game_board;

    int player_count = 2;

    int run_needed = 4;

    std::vector<Player*> player_vector;

    std::vector<char> player_tokens;

public:

    Game();

    ~Game();

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

