#include "gmock/gmock.h"
#include "MCTSNode.h"


class MockMCTSNode : public MCTSNode {
public:
    MOCK_METHOD0(hasUnvisitedChildren, bool());
    MOCK_METHOD0(selectChildNode, MCTSNode*());
    MOCK_METHOD0(getUnvisitedChildNode, MCTSNode*());
    MOCK_METHOD0(simulateGames, void());
    MOCK_METHOD0(backPropagateResults, void());
};