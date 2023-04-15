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

    int run_needed;

    std::vector<char> player_tokens;

    Board* game_board_pointer;

    int number_of_players;

    //int run_needed = 4;

    std::vector<Player*> player_vector;




public:

    Game();

    //~Game();

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

