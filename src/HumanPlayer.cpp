#include <iostream>
#include <limits> // for std::numeric_limits

#include "HumanPlayer.h"

void HumanPlayer::ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int HumanPlayer::get_move(int board_width){

    while (true)
    {
        std::cout << "Enter your column choice. First column is 1.";
        int selected_column{};
        std::cin >> selected_column;

        if (!std::cin)
        {
            std::cin.clear();
            HumanPlayer::ignoreLine();
            std::cerr << "Sorry, that input is invalid. Please try again.\n";
            continue;
        }

        if (selected_column > board_width){
            std::cin.clear();
            HumanPlayer::ignoreLine();
            std::cerr << "Sorry, that column number is too high. Please try again.\n";
            continue;
        }

        if (selected_column <= 0){
            std::cin.clear();
            HumanPlayer::ignoreLine();
            std::cerr << "Sorry, that column number is too low. The first column in 1. Please try again.\n";
            continue;
        }

        else
        {
            std::cin.clear();
            ignoreLine();
            std::cout << selected_column << std::endl;
            return selected_column -1;
        }
    }
}
