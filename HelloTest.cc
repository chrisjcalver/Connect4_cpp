#include <gtest/gtest.h>

#include <memory>
#include <vector>

#include "include/Board.h"
#include "Game.h"

namespace{



    //player_tokens_pointer

    TEST(Game, BoardWidth) {

        std::shared_ptr< std::vector<char> > player_tokens_pointer = std::make_shared< std::vector<char> >();

        Board test_board(6, 7, player_tokens_pointer, 4, 2);

        //Game this_game {};

        EXPECT_EQ(7, test_board.get_board_width());
//Game this_game {};

/*
    std::shared_ptr< std::vector<char> > player_tokens_pointer = std::make_shared< std::vector<char> >();

    const Board test_board(6, 7, player_tokens_pointer, 4, 2);


    */
}


// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}
}
