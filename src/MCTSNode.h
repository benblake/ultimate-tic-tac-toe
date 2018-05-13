#ifndef MCTS_NODE_H
#define MCTS_NODE_H


class MCTSNode {
public:
    // MCTSNode(MCTSNode *parentNode);
    // MCTSNode() {
    //     mNumberOfVisits = 0;
    // }

    // void visit() {
    //     mNumberOfVisits++;
    // }

    // int getNumberOfVisits() {
    //     return mNumberOfVisits;
    // }
    // virtual MCTSNode *determineLeafNode() = 0;
    virtual bool hasUnvisitedChildren() = 0;
    virtual MCTSNode *selectChildNode() = 0;
    virtual MCTSNode *getUnvisitedChildNode() = 0;
    virtual void simulateGames() = 0;
    virtual void backPropagateResults() = 0;

private:
    // int mNumberOfVisits;

// private:
//     MCTSNode *mParentNode;
};


#endif // MCTS_NODE_H