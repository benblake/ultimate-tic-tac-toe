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
    // for (int i = 0; i < 3; i++) {
    //     for (int j = 0; j < 3; j++) {
    //         validMoves.push_back(Cell(i, j));
    //     }
    // }
    GameState *gs = new GameState(playerACells, playerBCells, validMoves);

    // initialize MCTS tree with game state
    MCTS searchTree(gs);

    // round 1
    MCTSNode *selectedNode;
    MCTSNode *expandedNode;

        clock_t t = clock();

    // for (int i = 0; i < 10000; i++) {
    for (int i = 0; i < 1000; i++) {
        // clock_t t = clock();
        selectedNode = searchTree.select();

        // std::cout << "selected node player A cells" << std::endl;
        // selectedNode->printPlayerACells();
        // std::cout << "selected node player B cells" << std::endl;
        // selectedNode->printPlayerBCells();

        expandedNode = searchTree.expand(selectedNode);

        // std::cout << "expanded node player A cells" << std::endl;
        // expandedNode->printPlayerACells();
        // std::cout << "expanded node player B cells" << std::endl;
        // expandedNode->printPlayerBCells();

        for (int j = 0; j < 20; j++) {
        // bool playerAWins = searchTree.simulate(expandedNode);
        int gameResult = searchTree.simulate(expandedNode);
        // std::cout << "main game result = " << gameResult << std::endl;

        // searchTree.backPropagate(expandedNode, playerAWins);
        searchTree.backPropagate(expandedNode, gameResult);
        }

        // t = clock() - t;
        // std::cout << "iteration took " << ((float)t) / CLOCKS_PER_SEC << " seconds" << std::endl;

        // std::cout << "player a wins = " << playerAWins << std::endl;


        // expandedNode->printPlayerACells();
        // expandedNode->printResults();
        // std::cout << "-----------------------------------" << std::endl;
    }

        t = clock() - t;
        std::cout << "iteration took " << ((float)t) / CLOCKS_PER_SEC << " seconds" << std::endl;
    // selectedNode = searchTree.select();

    // selectedNode->printPlayerACells();

    searchTree.printRootResults();
    searchTree.printBestMove();


    // expandedNode->simulate();

    // expandedNode->setVisited();

    // round 2 and beyond
    // for (int i = 1; i < 10; i++) {
    //     selectedNode = searchTree.select();

    //     selectedNode->printPlayerACells();

    //     expandedNode = searchTree.expand(selectedNode);

    //     expandedNode->printPlayerACells();

    //     expandedNode->setVisited();
    // }

    // expandedNode->printChildNodes();




    return 0;
}