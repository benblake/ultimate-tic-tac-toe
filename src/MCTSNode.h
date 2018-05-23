#ifndef MCTS_NODE_H
#define MCTS_NODE_H

#include <cmath>
#include "GameState.h"
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
        for (MCTSNode *node : mChildNodes) {
            delete node;
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
        GameState gs = *mGameState;
        bool playerATurn = !mPlayerATurn;
        while (gs.getValidMoves().size() != 0) {
            // std::cout << "player A turn = " << playerATurn << std::endl;
            if (gs.playerAWins()) {
                // std::cout << "player A wins" << std::endl;
                return 1;
            } else if (gs.playerBWins()) {
                // std::cout << "player B wins" << std::endl;
                return -1;
            }

            std::vector<Cell> playerACells = gs.getPlayerACells();
            std::vector<Cell> playerBCells = gs.getPlayerBCells();
            std::vector<Cell> validMoves = gs.getValidMoves();

            int index = rand() % validMoves.size();
            if (playerATurn) {
                playerACells.push_back(validMoves[index]);
            } else {
                playerBCells.push_back(validMoves[index]);
            }

            // if (playerATurn) {
            //     std::cout << "player A move = " << validMoves[index].x << " " << validMoves[index].y << std::endl;
            // } else {
            //     std::cout << "player B move = " << validMoves[index].x << " " << validMoves[index].y << std::endl;
            // }

            validMoves.erase(validMoves.begin() + index);

            gs = GameState(playerACells, playerBCells, validMoves);

            playerATurn = !playerATurn;
        }
        if (gs.playerAWins()) {
            return 1;
        } else if (gs.playerBWins()) {
            return -1;
        } else {
            return 0;
        }
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