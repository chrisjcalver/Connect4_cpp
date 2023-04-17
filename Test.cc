#include <gtest/gtest.h>

#include <memory>
#include <vector>
#include <array>
#include <iostream>

#include "Game.h"
#include "Board.h"
#include "Player.h"
#include "BotPlayer.h"
#include "HumanPlayer.h"

namespace{



    //player_tokens_pointer

    TEST(Board, board_width) {

        std::shared_ptr< std::vector<char> > player_tokens_pointer = std::make_shared< std::vector<char> >();


        // Constructor is board_height, board_width, player_tokens_pointer, winning_run, number_of_player
        Board test_board(6, 7, player_tokens_pointer, 4, 2);

        //Game this_game {};

        EXPECT_EQ(7, test_board.get_board_width());
    }

            //player_tokens_pointer

    TEST(Board, make_move) {

        std::shared_ptr< std::vector<char> > player_tokens_pointer = std::make_shared< std::vector<char> >();

        //test initially failed becuase make_move() needs to update runs_count which needs a populated vector

        Board test_board(6, 7, player_tokens_pointer, 4, 2);

        player_tokens_pointer->push_back('x');

        player_tokens_pointer->push_back('o');

        int position1 = test_board.make_move('x', 0);
        int position2 = test_board.make_move('x', 0);
        int position3 = test_board.make_move('x', 1);

        EXPECT_EQ(35, position1 );
        EXPECT_EQ(28, position2 );
        EXPECT_EQ(36, position3 );

        std::cerr << "[          ] position1 = " << position1 << std::endl;
    }

    TEST(Board, horizontal_win) {

        std::shared_ptr< std::vector<char> > player_tokens_pointer = std::make_shared< std::vector<char> >();

        player_tokens_pointer->push_back('x');
        player_tokens_pointer->push_back('o');

        Board test_board(6, 7, player_tokens_pointer, 4, 2);

        int left_most_position = test_board.make_move('x', 0);
        test_board.make_move('x', 1);
        test_board.make_move('x', 2);
        int right_most_position = test_board.make_move('x', 3);

        // test for win takes player number and board_position as input
        EXPECT_EQ(true, test_board.check_for_win( 'x', left_most_position) );
        EXPECT_EQ(true, test_board.check_for_win( 'x', right_most_position) );
    }

    TEST(Board, vertical_win) {

        std::shared_ptr< std::vector<char> > player_tokens_pointer = std::make_shared< std::vector<char> >();

        player_tokens_pointer->push_back('x');
        player_tokens_pointer->push_back('o');

        Board test_board(6, 7, player_tokens_pointer, 4, 2);

        int top_most_position = test_board.make_move('x', 0);
        test_board.make_move('x', 0);
        test_board.make_move('x', 0);
        int bottom_most_position = test_board.make_move('x', 0);

        // test for win takes player number and board_position as input
        EXPECT_EQ(true, test_board.check_for_win( 'x', top_most_position) );
        EXPECT_EQ(true, test_board.check_for_win( 'x', bottom_most_position) );
    }

    TEST(Board, up_left_win) {

        std::shared_ptr< std::vector<char> > player_tokens_pointer = std::make_shared< std::vector<char> >();

        player_tokens_pointer->push_back('x');
        player_tokens_pointer->push_back('o');

        Board test_board(6, 7, player_tokens_pointer, 4, 2);

        test_board.make_move('o', 0);
        test_board.make_move('o', 0);
        test_board.make_move('o', 0);
        int top_most_position = test_board.make_move('x', 0);

        test_board.make_move('o', 1);
        test_board.make_move('o', 1);
        test_board.make_move('x', 1);

        test_board.make_move('o', 2);
        test_board.make_move('x', 2);

        int bottom_most_position = test_board.make_move('x', 3);

        // test for win takes player number and board_position as input
        EXPECT_EQ(true, test_board.check_for_win( 'x', top_most_position) );
        EXPECT_EQ(true, test_board.check_for_win( 'x', bottom_most_position) );
    }

    TEST(Board, up_right_win) {

        std::shared_ptr< std::vector<char> > player_tokens_pointer = std::make_shared< std::vector<char> >();

        player_tokens_pointer->push_back('x');
        player_tokens_pointer->push_back('o');

        Board test_board(6, 7, player_tokens_pointer, 4, 2);

        int bottom_most_position = test_board.make_move('x', 0);


        test_board.make_move('o', 1);
        test_board.make_move('x', 1);

        test_board.make_move('o', 2);
        test_board.make_move('o', 2);
        test_board.make_move('x', 2);


        test_board.make_move('o', 3);
        test_board.make_move('o', 3);
        test_board.make_move('o', 3);
        int top_most_position = test_board.make_move('x', 3);


        //Game this_game {};

        // test for win takes player number and board_position as input
        EXPECT_EQ(true, test_board.check_for_win( 'x', top_most_position) );
        EXPECT_EQ(true, test_board.check_for_win( 'x', bottom_most_position) );
    }


    TEST(Board, check_draw) {

        std::shared_ptr< std::vector<char> > player_tokens_pointer = std::make_shared< std::vector<char> >();

        player_tokens_pointer->push_back('x');
        player_tokens_pointer->push_back('o');

        Board test_board(6, 7, player_tokens_pointer, 4, 2);

        for (int column = 0; column < 7; column++){

            for( int row = 0; row < 6; row++){

                test_board.make_move('x', column);
            }
        }

        EXPECT_EQ(true, test_board.check_for_draw() );
    }

    TEST(Game, full_run){

        Game test_game {};

        int turn_number = test_game.run_game();

        EXPECT_EQ(turn_number, 36 );

    }

} //namespace
