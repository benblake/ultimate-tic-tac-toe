#ifndef MCTS_NODE_H
#define MCTS_NODE_H

#include <cmath>
#include "GameState.h"
#include "GameSimulator.h"
#include "time.h"

class MCTSNode {
private:
    int mNumberOfVisits;
    int mNumberOfWins;
    MCTSNode *mParentNode;
    GameState *mGameState;
    bool mPlayerATurn;
    std::vector<MCTSNode *> mChildNodes;

public:
    MCTSNode(MCTSNode *parentNode, GameState *gs, bool playerATurn) {
        srand(time(NULL));
        mParentNode = parentNode;
        mGameState = gs;
        mPlayerATurn = playerATurn;
        mNumberOfVisits = 0;
        mNumberOfWins = 0;
    }

    ~MCTSNode() {
        delete mGameState;
        mGameState = nullptr;
        for (MCTSNode *node : mChildNodes) {
            delete node;
            node = nullptr;
        }
    }

    bool hasUnvisitedChildren() {
        if (mChildNodes.size() == 0) {
            return true;
        }
        for (MCTSNode *node : mChildNodes) {
            if (node->getNumberOfVisits() == 0) {
                return true;
            }
        }
        return false;
    }

    MCTSNode *selectChildNode() {
        MCTSNode *childNode = mChildNodes[0];
        double maxSelectionValue = childNode->upperConfidenceBound(mNumberOfVisits);

        for (MCTSNode *node : mChildNodes) {
            double selectionValue = node->upperConfidenceBound(mNumberOfVisits);
            if (selectionValue > maxSelectionValue) {
                maxSelectionValue = selectionValue;
                childNode = node;
            }
        }

        return childNode;
    }

    MCTSNode *getUnvisitedChildNode() {
        if (mChildNodes.size() == 0) {
            generateChildNodes();
        }
        return getFirstUnvisitedChildNode();
    }

    int simulateGames() {
        GameSimulator gameSimulator;
        return gameSimulator.simulateGame(*mGameState, !mPlayerATurn);
    }

    void backPropagateResults(int gameResult) {
        mNumberOfVisits++;
        mNumberOfWins += gameResult;

        if (mParentNode != nullptr) {
            mParentNode->backPropagateResults(gameResult);
        }
    }

    void printResults() {
        std::cout << mNumberOfWins << "/" << mNumberOfVisits << std::endl;
    }

    void printBestMove() {
        MCTSNode *childNode = mChildNodes[0];
        double maxSelectionValue = childNode->getWinRatio();

        for (MCTSNode *node : mChildNodes) {
            double selectionValue = node->getWinRatio();
            if (selectionValue > maxSelectionValue) {
                maxSelectionValue = selectionValue;
                childNode = node;
            }
        }
        childNode->printPlayerACells();
    }

    void printPlayerACells() {
        mGameState->printPlayerACells();
    }

    void printPlayerBCells() {
        mGameState->printPlayerBCells();
    }

    void printValidMoves() {
        mGameState->printValidMoves();
    }

private:
    int getNumberOfVisits() {
        return mNumberOfVisits;
    }

    int getNumberOfWins() {
        return mNumberOfWins;
    }

    double upperConfidenceBound(int parentNumberOfVisits) {
        double ucb = (double) mNumberOfWins / (double) mNumberOfVisits;
        ucb += 2 * sqrt(log((double) parentNumberOfVisits) / (double) mNumberOfVisits);

        return ucb;
    }

    double getWinRatio() {
        return (double) mNumberOfWins / (double) mNumberOfVisits;
    }

    void generateChildNodes() {
        std::vector<Cell> playerACells = mGameState->getPlayerACells();
        std::vector<Cell> playerBCells = mGameState->getPlayerBCells();
        std::vector<Cell> validMoves = mGameState->getValidMoves();

        for (size_t i = 0; i < validMoves.size(); i++) {
            if (mPlayerATurn) { // children will be player B turn
                playerBCells.push_back(validMoves[i]);
            } else {
                playerACells.push_back(validMoves[i]);
            }
            std::vector<Cell> newValidMoves;
            for (size_t j = 0; j < validMoves.size(); j++) {
                if (j != i) {
                    newValidMoves.push_back(validMoves[j]);
                }
            }
            GameState *gs = new GameState(playerACells, playerBCells, newValidMoves);
            mChildNodes.push_back(new MCTSNode(this, gs, !mPlayerATurn));
            if (mPlayerATurn) { // children will be player B turn
                playerBCells.pop_back();
            } else {
                playerACells.pop_back();
            }
        }
    }

    MCTSNode *getFirstUnvisitedChildNode() {
        for (MCTSNode *node : mChildNodes) {
            if (node->getNumberOfVisits() == 0) {
                return node;
            }
        }
        return this; // if no child nodes must be a leaf
    }

    void printChildNodes() {
        for (size_t i = 0; i < mChildNodes.size(); i++) {
            std::cout << "NODE " << i << "-----------------------" << std::endl;

            mChildNodes[i]->printPlayerACells();
            std::cout << "-----------------------" << std::endl;

            mChildNodes[i]->printValidMoves();
        }
    }

    void setVisited() {
        mNumberOfVisits++;
    }
};

#endif // MCTS_NODE_H