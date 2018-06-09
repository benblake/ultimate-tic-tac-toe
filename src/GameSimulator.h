#ifndef GAME_SIMULATOR_H
#define GAME_SIMULATOR_H

#include "GameState.h"

class GameSimulator {
public:
    int simulateGame(GameState gameState, bool playerATurn) {
        while (gameState.getValidMoves().size() != 0) {
            if (gameState.playerAWins()) {
                return 1;
            } else if (gameState.playerBWins()) {
                return -1;
            }

            gameState = advanceGameState(gameState, playerATurn);

            playerATurn = !playerATurn;
        }

        return gameEndCondition(gameState);
    }

private:
    int gameEndCondition(const GameState &gameState) {
        if (gameState.playerAWins()) {
            return 1;
        } else if (gameState.playerBWins()) {
            return -1;
        } else {
            return 0;
        }
    }

    GameState advanceGameState(const GameState &gameState, bool playerATurn) {
        std::vector<Cell> playerACells = gameState.getPlayerACells();
        std::vector<Cell> playerBCells = gameState.getPlayerBCells();
        std::vector<Cell> validMoves = gameState.getValidMoves();

        int index = rand() % validMoves.size();
        if (playerATurn) {
            playerACells.push_back(validMoves[index]);
        } else {
            playerBCells.push_back(validMoves[index]);
        }

        validMoves.erase(validMoves.begin() + index);

        return GameState(playerACells, playerBCells, validMoves);
    }
};

#endif // GAME_SIMULATOR_H