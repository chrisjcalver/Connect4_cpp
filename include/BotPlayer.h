#ifndef BOT_PLAYER_H
#define BOT_PLAYER_H

#include <memory>

#include "Player.h"
#include "Board.h"

class BotPlayer : public Player
{
    // The winValue is here to mark which moves ( such as choosing a full column, are a really bad option. )
    int winValue = 10000;

public:

    BotPlayer(std::shared_ptr<Board> game_board_pointer, int player_number) : Player( game_board_pointer , player_number){

        //std::cout << "Bot Player initialized" << std::endl;
        //std::cout << game_board_pointer->get_board_width << std::endl;
        //std::cout << "board_width is: " << this->board_width << std::endl;
        };


    int get_move() override;

    int checkForWin(char token);

    int checkForThisPlayerTwoMoveWin();

    int checkForNextPlayerTwoMoveWin();

    std::array<int,2> getWinCountWinningColumn (char given_token);

    std::array<int,2> getBestRelativeMoveColumnValue (char given_token);

    int getRelativeMoveValue (char given_token, int column);





    //bool check_for_potential_win(char check_token);
};

#endif
