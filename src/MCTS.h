#ifndef MCTS_H
#define MCTS_H

#include "MCTSNode.h"

class MCTS {

private:
    MCTSNode *mRootNode;

public:
    MCTS(MCTSNode *rootNode) {
        mRootNode = rootNode;
    }

    MCTSNode *select() {
        MCTSNode *currentNode = mRootNode;
        while (!currentNode->hasUnvisitedChildren()) {
            currentNode = currentNode->selectChildNode();
        }
        return currentNode;
    }

    MCTSNode *expand(MCTSNode *parentNode) {
        return parentNode->getUnvisitedChildNode();
    }

    void simulate(MCTSNode *node) {
        node->simulateGames();
    }

    void backPropagate(MCTSNode *node) {
        node->backPropagateResults();
    }

    void iterate() {
        MCTSNode *childNode = select();
        MCTSNode *unvisitedNode = expand(childNode);
        simulate(unvisitedNode);
        backPropagate(unvisitedNode);
    }
};


#endif // MCTS_H