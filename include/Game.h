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

    int board_height;

    int board_width;

    int run_needed;

    //std::vector<char> player_tokens;

    std::shared_ptr<Board> game_board_pointer;

    int number_of_players;

    std::array<std::shared_ptr<Player>, 2> player_array;


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

