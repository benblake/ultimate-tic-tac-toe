#include "TicTacToeGame.h"
#include "gtest/gtest.h"
// namespace {

TEST(TicTacToeGameTest, ReturnsTrue) {
    TicTacToeGame game;
    EXPECT_TRUE(game.returnTrue());
}

// } // namespace