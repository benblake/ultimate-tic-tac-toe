#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <vector>

#include "GameState.h"

// Tests for if play A (us) won
namespace {
TEST(GameStatePlayerAWins, PlayerAWinsWithRowOne) {
    std::vector<Cell> playerACells;
    std::vector<Cell> playerBCells;
    std::vector<Cell> validMoves;
    playerACells.push_back(Cell(0, 0));
    playerACells.push_back(Cell(1, 0));
    playerACells.push_back(Cell(2, 0));

    GameState gs(playerACells, playerBCells, validMoves);

    EXPECT_TRUE(gs.playerAWins());
}

TEST(GameStatePlayerAWins, PlayerAWinsWithRowTwo) {
    std::vector<Cell> playerACells;
    std::vector<Cell> playerBCells;
    std::vector<Cell> validMoves;
    playerACells.push_back(Cell(0, 1));
    playerACells.push_back(Cell(1, 1));
    playerACells.push_back(Cell(2, 1));

    GameState gs(playerACells, playerBCells, validMoves);

    EXPECT_TRUE(gs.playerAWins());
}

TEST(GameStatePlayerAWins, PlayerAWinsWithRowThree) {
    std::vector<Cell> playerACells;
    std::vector<Cell> playerBCells;
    std::vector<Cell> validMoves;
    playerACells.push_back(Cell(0, 2));
    playerACells.push_back(Cell(1, 2));
    playerACells.push_back(Cell(2, 2));

    GameState gs(playerACells, playerBCells, validMoves);

    EXPECT_TRUE(gs.playerAWins());
}

TEST(GameStatePlayerAWins, PlayerAWinsWithColOne) {
    std::vector<Cell> playerACells;
    std::vector<Cell> playerBCells;
    std::vector<Cell> validMoves;
    playerACells.push_back(Cell(0, 0));
    playerACells.push_back(Cell(0, 1));
    playerACells.push_back(Cell(0, 2));

    GameState gs(playerACells, playerBCells, validMoves);

    EXPECT_TRUE(gs.playerAWins());
}

TEST(GameStatePlayerAWins, PlayerAWinsWithColTwo) {
    std::vector<Cell> playerACells;
    std::vector<Cell> playerBCells;
    std::vector<Cell> validMoves;
    playerACells.push_back(Cell(1, 0));
    playerACells.push_back(Cell(1, 1));
    playerACells.push_back(Cell(1, 2));

    GameState gs(playerACells, playerBCells, validMoves);

    EXPECT_TRUE(gs.playerAWins());
}

TEST(GameStatePlayerAWins, PlayerAWinsWithColThree) {
    std::vector<Cell> playerACells;
    std::vector<Cell> playerBCells;
    std::vector<Cell> validMoves;
    playerACells.push_back(Cell(2, 0));
    playerACells.push_back(Cell(2, 1));
    playerACells.push_back(Cell(2, 2));

    GameState gs(playerACells, playerBCells, validMoves);

    EXPECT_TRUE(gs.playerAWins());
}

TEST(GameStatePlayerAWins, PlayerAWinsWithDiagOne) {
    std::vector<Cell> playerACells;
    std::vector<Cell> playerBCells;
    std::vector<Cell> validMoves;
    playerACells.push_back(Cell(0, 0));
    playerACells.push_back(Cell(1, 1));
    playerACells.push_back(Cell(2, 2));

    GameState gs(playerACells, playerBCells, validMoves);

    EXPECT_TRUE(gs.playerAWins());
}

TEST(GameStatePlayerAWins, PlayerAWinsWithDiagTwo) {
    std::vector<Cell> playerACells;
    std::vector<Cell> playerBCells;
    std::vector<Cell> validMoves;
    playerACells.push_back(Cell(0, 2));
    playerACells.push_back(Cell(1, 1));
    playerACells.push_back(Cell(2, 0));

    GameState gs(playerACells, playerBCells, validMoves);

    EXPECT_TRUE(gs.playerAWins());
}
}

int main(int argc, char** argv) {
  // The following line must be executed to initialize Google Mock
  // (and Google Test) before running the tests.
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}