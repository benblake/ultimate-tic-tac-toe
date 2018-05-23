#ifndef MCTS_H
#define MCTS_H

#include "MCTSNode.h"
#include "GameState.h"

class MCTS {

private:
    MCTSNode *mRootNode;

public:
    MCTS(GameState *gs) {
        mRootNode = new MCTSNode(nullptr, gs, false);
    }

    ~MCTS() {
        delete mRootNode;
        mRootNode = nullptr;
    }

    void printRootResults() {
        mRootNode->printResults();
    }

    void printBestMove() {
        mRootNode->printBestMove();
    }

    void iterate() {
        MCTSNode *selectedNode = select();

        MCTSNode *expandedNode = expand(selectedNode);

        for (int j = 0; j < 20; j++) {
            int gameResult = simulate(expandedNode);
            backPropagate(expandedNode, gameResult);
        }
    }

private:
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

    int simulate(MCTSNode *node) {
        return node->simulateGames();
    }

    void backPropagate(MCTSNode *node, int gameResult) {
        node->backPropagateResults(gameResult);
    }
};

#endif // MCTS_H