#include "Game.h"

Game::Game(){
        //default initialisation

    //Player player1{};

    //Player player2{};

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
    return;
    }

