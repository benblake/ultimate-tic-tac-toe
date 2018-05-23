#ifndef MCTS_NODE_H
#define MCTS_NODE_H

#include <cmath>
#include "GameState.h"
#include "time.h"

class MCTSNode {
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

    void printPlayerACells() {
        mGameState->printPlayerACells();
    }

    void printPlayerBCells() {
        mGameState->printPlayerBCells();
    }

    void printValidMoves() {
        mGameState->printValidMoves();
    }

    void printBestMove() {
        MCTSNode *childNode = mChildNodes[0];
        double maxSelectionValue = upperConfidenceBound2(mChildNodes[0]);

        for (MCTSNode *node : mChildNodes) {
            double selectionValue = upperConfidenceBound2(node);
            if (selectionValue > maxSelectionValue) {
                maxSelectionValue = selectionValue;
                childNode = node;
            }
        }
        // std::cout << "maxSelectionValue = " << maxSelectionValue << std::endl;
        // std::cout << childNode->getNumberOfWins() << "/" << childNode->getNumberOfVisits() << std::endl;
        childNode->printPlayerACells();
    }
    // MCTSNode(MCTSNode *parentNode) {
    //     MCTSNode();
    //     mParentNode = parentNode;
    // }
    // MCTSNode() {
    //     mParentNode = nullptr;
    //     mGameState = nullptr;
    //     mNumberOfVisits = 0;
    // }

    int getNumberOfVisits() {
        return mNumberOfVisits;
    }

    int getNumberOfWins() {
        return mNumberOfWins;
    }

    // std::vector<MCTSNode *> getChildren() {
    //     return mChildNodes;
    // }

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
        double maxSelectionValue = upperConfidenceBound(mChildNodes[0]);

        for (MCTSNode *node : mChildNodes) {
            double selectionValue = upperConfidenceBound(node);
            if (selectionValue > maxSelectionValue) {
                maxSelectionValue = selectionValue;
                childNode = node;
            }
        }
                // std::cout << "maxSelectionValue = " << maxSelectionValue << std::endl;

        return childNode;
    }

    double upperConfidenceBound(MCTSNode *childNode) {
        double ucb = (double) childNode->getNumberOfWins() /
                     (double) childNode->getNumberOfVisits();
        // ucb += 1 * sqrt(log((double) mNumberOfVisits) / (double) childNode->getNumberOfVisits());
        ucb += 2 * sqrt(log((double) mNumberOfVisits) / (double) childNode->getNumberOfVisits());

        return ucb;
    }

    double upperConfidenceBound2(MCTSNode *childNode) {
        double ucb = (double) childNode->getNumberOfWins() /
                     (double) childNode->getNumberOfVisits();

        return ucb;
    }
    
    MCTSNode *getUnvisitedChildNode() {
        if (mChildNodes.size() == 0) {
            generateChildNodes();
        }
        return getFirstUnvisitedChildNode();
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


    int simulateGames() {
        // srand(time(NULL));
        std::vector<Cell> playerACells = mGameState->getPlayerACells();
        std::vector<Cell> playerBCells = mGameState->getPlayerBCells();
        std::vector<Cell> validMoves = mGameState->getValidMoves();
        GameState gs(playerACells, playerBCells, validMoves);
        // GameState gs = *mGameState;
        bool playerATurn = !mPlayerATurn;
        while (gs.getValidMoves().size() != 0) {
            // std::cout << "player A turn = " << playerATurn << std::endl;
            if (gs.playerAWins()) {
                // return true;
                // std::cout << "player A wins" << std::endl;
                // printPlayerACells();
                return 1;
            } else if (gs.playerBWins()) {
                // return false;
                // std::cout << "player B wins" << std::endl;
                // printPlayerBCells();
                return -1;
            }

            std::vector<Cell> playerACells = gs.getPlayerACells();
            std::vector<Cell> playerBCells = gs.getPlayerBCells();
            std::vector<Cell> validMoves = gs.getValidMoves();

            int index = rand() % validMoves.size();
            // int index = 0;
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
            // return true;
            return 1;
        // } else {
        } else if (gs.playerBWins()) {
            // return false;
            return -1;
        } else {
            return 0;
        }
    }

    // void backPropagateResults(bool playerAWins) {
    void backPropagateResults(int gameResult) {
        mNumberOfVisits++;
        // if (playerAWins) {
            // mNumberOfWins++;
            mNumberOfWins += gameResult;
        // }
        if (mParentNode != nullptr) {
            // mParentNode->backPropagateResults(playerAWins);
            mParentNode->backPropagateResults(gameResult);
        }
    }

    void printResults() {
        std::cout << mNumberOfWins << "/" << mNumberOfVisits << std::endl;
    }

private:
    int mNumberOfVisits;
    int mNumberOfWins;
    MCTSNode *mParentNode;
    GameState *mGameState;
    bool mPlayerATurn;
    std::vector<MCTSNode *> mChildNodes;
};


#endif // MCTS_NODE_H