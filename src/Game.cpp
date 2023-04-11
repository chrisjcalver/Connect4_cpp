#include "Game.h"
#include "Player.h"
#include "BotPlayer.h"
#include "HumanPlayer.h"


Game::Game(){
        //default initialisation

    BotPlayer player1{};

    HumanPlayer player2{};

    std::cout<<"game initialized"<< std::endl;

}



void Game::print_game_board(){
    std::cout << "trying to print board"<<std::endl;
    this->game_board.print_board();
    return;
    }

void Game::run_game(){
    std::cout << "running game" << std::endl;
    Game::print_game_board();
    std::cout << player1.get_move();
    std::cout << player2.get_move();

    return;
    }

