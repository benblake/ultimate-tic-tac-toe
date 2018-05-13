#ifndef MCTS_H
#define MCTS_H

#include "MCTSNode.h"


class MCTS {
public:
    MCTS(MCTSNode *rootNode) {
        mRootNode = rootNode;
    }

    MCTSNode *select() {
        MCTSNode *currentNode = mRootNode;
        while (!currentNode->isLeafNode()) {
            currentNode = currentNode->selectChildNode();
        }
        return currentNode;
    }
    

private:
    MCTSNode *mRootNode;
};


#endif // MCTS_H