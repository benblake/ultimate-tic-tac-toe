#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "MCTS.h"
#include "MockMCTSNode.h"

// using ::testing::AtLeast;
using ::testing::Return;

// Tests for select method
namespace {
TEST(MCTSSelectTest, SelectReturnsRootNodeRootIsALeaf) {
    MockMCTSNode mockRootNode;
    EXPECT_CALL(mockRootNode, hasUnvisitedChildren())
        .Times(1)
        .WillOnce(Return(true));

    MCTS searchTree(&mockRootNode);

    EXPECT_EQ(&mockRootNode, searchTree.select());
}

TEST(MCTSSelectTest, SelectCallsGetsRootsChildIfItIsNotALeaf) {
    MockMCTSNode mockRootNode;
    MockMCTSNode mockChildNode;

    EXPECT_CALL(mockRootNode, hasUnvisitedChildren())
        .Times(1)
        .WillOnce(Return(false));
    EXPECT_CALL(mockChildNode, hasUnvisitedChildren())
        .Times(1)
        .WillOnce(Return(true));

    EXPECT_CALL(mockRootNode, selectChildNode())
        .Times(1)
        .WillOnce(Return(&mockChildNode));

    MCTS searchTree(&mockRootNode);

    EXPECT_EQ(&mockChildNode, searchTree.select());
}

TEST(MCTSSelectTest, SelectTraversesUntilItFindsALeafNode) {
    MockMCTSNode mockRootNode;
    MockMCTSNode mockChildNode1;
    MockMCTSNode mockChildNode2;

    EXPECT_CALL(mockRootNode, hasUnvisitedChildren())
        .Times(1)
        .WillOnce(Return(false));
    EXPECT_CALL(mockChildNode1, hasUnvisitedChildren())
        .Times(1)
        .WillOnce(Return(false));
    EXPECT_CALL(mockChildNode2, hasUnvisitedChildren())
        .Times(1)
        .WillOnce(Return(true));

    EXPECT_CALL(mockRootNode, selectChildNode())
        .Times(1)
        .WillOnce(Return(&mockChildNode1));
    EXPECT_CALL(mockChildNode1, selectChildNode())
        .Times(1)
        .WillOnce(Return(&mockChildNode2));

    MCTS searchTree(&mockRootNode);

    EXPECT_EQ(&mockChildNode2, searchTree.select());
}
}

// Tests for expand method
namespace {
TEST(MCTSExpandTest, ExpandReturnsNewUnvisitedChild) {
    MockMCTSNode mockParentNode;
    MockMCTSNode mockUnvisitedChildNode;

    EXPECT_CALL(mockParentNode, getUnvisitedChildNode())
        .Times(1)
        .WillOnce(Return(&mockUnvisitedChildNode));

    MCTS searchTree(nullptr);

    EXPECT_EQ(&mockUnvisitedChildNode, searchTree.expand(&mockParentNode));
}
}

// Tests for simulate method
namespace {
TEST(MCTSSimulateTest, SimulateCallsSimulateOnPassedInNode) {
    MockMCTSNode mockNode;

    EXPECT_CALL(mockNode, simulateGames())
        .Times(1);

    MCTS searchTree(nullptr);

    searchTree.simulate(&mockNode);
}
}

// Tests for backPropagate method
namespace {
TEST(MCTSBackPropagateTest, BackPropagateCallsNodeToBackPropogateResults) {
    MockMCTSNode mockNode;

    EXPECT_CALL(mockNode, backPropagateResults())
        .Times(1);

    MCTS searchTree(nullptr);

    searchTree.backPropagate(&mockNode);
}
}

// Tests for iterate method
namespace {
TEST(MCTSIterateTest, IterateConsistsOfOneLoopOfAllMethods) {
    MockMCTSNode mockRootNode;
    MockMCTSNode mockChildNode;
    MockMCTSNode mockUnvisitedNode;

    EXPECT_CALL(mockRootNode, hasUnvisitedChildren())
        .Times(1)
        .WillOnce(Return(false));
    EXPECT_CALL(mockChildNode, hasUnvisitedChildren())
        .Times(1)
        .WillOnce(Return(true));

    EXPECT_CALL(mockRootNode, selectChildNode())
        .Times(1)
        .WillOnce(Return(&mockChildNode));

    EXPECT_CALL(mockChildNode, getUnvisitedChildNode())
        .Times(1)
        .WillOnce(Return(&mockUnvisitedNode));

    EXPECT_CALL(mockUnvisitedNode, simulateGames())
        .Times(1);

    EXPECT_CALL(mockUnvisitedNode, backPropagateResults())
        .Times(1);

    MCTS searchTree(&mockRootNode);
    searchTree.iterate();
}
}

int main(int argc, char** argv) {
  // The following line must be executed to initialize Google Mock
  // (and Google Test) before running the tests.
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}