#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <vector>

class Cell {
public:
    int x, y;
    Cell(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

class GameState {
public:
    GameState(std::vector<Cell> playerACells, std::vector<Cell> playerBCells, std::vector<Cell> validMoves) {
        mPlayerACells = playerACells;
        mPlayerBCells = playerBCells;
        mValidMoves = validMoves;
    }

    bool playerAWins() {
        return playerWins(mPlayerACells);
    }

    bool playerBWins() {
        return playerWins(mPlayerBCells);
    }

private:
    std::vector<Cell> mPlayerACells;
    std::vector<Cell> mPlayerBCells;
    std::vector<Cell> mValidMoves;

    bool playerWins(std::vector<Cell> &playerCells) {
        int rowTally[3] = {0, 0, 0};
        int colTally[3] = {0, 0, 0};
        int diagTally[3] = {0, 0, 0};
        for (const Cell &c : playerCells) {
            rowTally[c.y]++;
            colTally[c.x]++;
            if (c.x == c.y) {
                diagTally[0]++;
            }
            if (c.x + c.y == 2) {
                diagTally[1]++;
            }
        }
        for (int i = 0; i < 3; i++) {
            if (rowTally[i] == 3 || colTally[i] == 3 || diagTally[i] == 3) {
                return true;
            }
        }
        return false;
    }
};


#endif // GAME_STATE_H