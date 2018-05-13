#include "gmock/gmock.h"
#include "MCTSNode.h"


class MockMCTSNode : public MCTSNode {
public:
    // MOCK_METHOD0(determineLeafNode, MCTSNode*());
    MOCK_METHOD0(isLeafNode, bool());
    MOCK_METHOD0(selectChildNode, MCTSNode*());

};