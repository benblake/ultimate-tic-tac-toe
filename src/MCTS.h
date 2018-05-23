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

    ~MCTS() {}

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

    // bool simulate(MCTSNode *node) {
    int simulate(MCTSNode *node) {
        return node->simulateGames();
    }

    // void backPropagate(MCTSNode *node, bool playerAWins) {
    void backPropagate(MCTSNode *node, int gameResult) {
        // node->backPropagateResults(playerAWins);
        node->backPropagateResults(gameResult);
    }

    void printRootResults() {
        mRootNode->printResults();
    }

    void printBestMove() {
        mRootNode->printBestMove();
    }

    // void iterate() {
    //     MCTSNode *childNode = select();
    //     MCTSNode *unvisitedNode = expand(childNode);
    //     simulate(unvisitedNode);
    //     backPropagate(unvisitedNode);
    // }
};


#endif // MCTS_H