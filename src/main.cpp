#include <iostream>
#include <vector>

#include "time.h"

#include "GameState.h"
#include "MCTS.h"


int main() {
    // initial game state
    std::vector<Cell> playerACells {
        Cell(1,1),
        Cell(2,0)
    };
    std::vector<Cell> playerBCells {
        Cell(0,2),
        Cell(2,2)
    };
    std::vector<Cell> validMoves = {
        Cell(0,0),
        Cell(0,1),
        Cell(1,0),
        Cell(1,2),
        Cell(2,1),
        
    };

    GameState *gs = new GameState(playerACells, playerBCells, validMoves);

    // initialize MCTS tree with game state
    MCTS searchTree(gs);

    // MCTSNode *selectedNode;
    // MCTSNode *expandedNode;

    clock_t t = clock();

    // for (int i = 0; i < 10000; i++) {
    for (int i = 0; i < 1000; i++) {
        // selectedNode = searchTree.select();

        // expandedNode = searchTree.expand(selectedNode);

        // for (int j = 0; j < 20; j++) {
        //     int gameResult = searchTree.simulate(expandedNode);
        //     searchTree.backPropagate(expandedNode, gameResult);
        // }
        searchTree.iterate();
    }

    t = clock() - t;
    std::cout << "iteration took " << ((float)t) / CLOCKS_PER_SEC << " seconds" << std::endl;
    // selectedNode = searchTree.select();

    // selectedNode->printPlayerACells();

    searchTree.printRootResults();
    searchTree.printBestMove();

    return 0;
}