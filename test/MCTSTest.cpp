// #include "path/to/mock-turtle.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "MCTS.h"
#include "MockMCTSNode.h"

// using ::testing::AtLeast;
using ::testing::Return;

TEST(MCTSTest, SelectReturnsRootNodeRootIsALeaf) {
    MockMCTSNode mockRootNode;
    EXPECT_CALL(mockRootNode, isLeafNode())
        .Times(1)
        .WillOnce(Return(true));

    MCTS searchTree(&mockRootNode);

    EXPECT_EQ(&mockRootNode, searchTree.select());
}

TEST(MCTSTest, SelectCallsGetsRootsChildIfItIsNotALeaf) {
    MockMCTSNode mockRootNode;
    MockMCTSNode mockChildNode;

    EXPECT_CALL(mockRootNode, isLeafNode())
        .Times(1)
        .WillOnce(Return(false));
    EXPECT_CALL(mockChildNode, isLeafNode())
        .Times(1)
        .WillOnce(Return(true));

    EXPECT_CALL(mockRootNode, selectChildNode())
        .Times(1)
        .WillOnce(Return(&mockChildNode));

    MCTS searchTree(&mockRootNode);

    EXPECT_EQ(&mockChildNode, searchTree.select());
}

TEST(MCTSTest, SelectTraversesUntilItFindsALeafNode) {
    MockMCTSNode mockRootNode;
    MockMCTSNode mockChildNode1;
    MockMCTSNode mockChildNode2;

    EXPECT_CALL(mockRootNode, isLeafNode())
        .Times(1)
        .WillOnce(Return(false));
    EXPECT_CALL(mockChildNode1, isLeafNode())
        .Times(1)
        .WillOnce(Return(false));
    EXPECT_CALL(mockChildNode2, isLeafNode())
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

int main(int argc, char** argv) {
  // The following line must be executed to initialize Google Mock
  // (and Google Test) before running the tests.
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}