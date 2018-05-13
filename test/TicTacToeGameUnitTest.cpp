#include "TicTacToeGame.h"
#include "MCTSNode.h"
#include "gtest/gtest.h"
// namespace {

// TEST(TicTacToeGameTest, ReturnsTrue) {
//     TicTacToeGame game;
//     EXPECT_TRUE(game.returnTrue());
// }

TEST(MCTSNodeTest, numberOfNodesInitializedToZero) {
    MCTSNode node;

    EXPECT_EQ(0, node.getNumberOfVisits());
}

TEST(MCTSNodeTest, numberOfNodesIncreasesEveryTimeVisited) {
    MCTSNode node;
    node.visit();
    node.visit();

    EXPECT_EQ(2, node.getNumberOfVisits());
}



// } // namespace