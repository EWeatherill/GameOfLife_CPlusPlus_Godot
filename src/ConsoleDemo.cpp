/**
This demo file is purely here to run Game of Life in a console window.
It is not build into the GameOfLife library file.
**/

#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <set>
#include <vector>

#include "GameOfLife.hpp"

using std::vector;
using std::pair;
using std::cout;
using std::endl;

// Grid type definition
using grid = vector<std::vector<bool>>;

// Properties to change for fun.
pair constexpr GRID_DIMENSIONS{ 15, 15 };
int constexpr MAX_EVOLUTIONS = 30;

// Forward declarations
void setRandomAliveCells(GameOfLife & gameOfLife);
pair<int, int> determineCellFromInt(int value);
void drawGrid(grid const & currentGrid);


int main()
{
    GameOfLife gameOfLife(GRID_DIMENSIONS.first, GRID_DIMENSIONS.second);
    setRandomAliveCells(gameOfLife);

    cout << "Starting grid: " << endl;
    drawGrid(gameOfLife.GetGrid());

    while (gameOfLife.GetCurrentEvolutionNumber() < MAX_EVOLUTIONS && 
        gameOfLife.Evolve()){

        cout << "Evolution " << gameOfLife.GetCurrentEvolutionNumber() << endl;
        drawGrid(gameOfLife.GetGrid());
    }

    cout << "Evolution ended" << endl;
    return 0;
}


void setRandomAliveCells(GameOfLife & gameOfLife){

    std::random_device randomDevice;
    std::mt19937 randomGenerator(randomDevice());
    std::uniform_int_distribution<int> distribution(
        0, GRID_DIMENSIONS.first * GRID_DIMENSIONS.second - 1);

    int numberOfCellsToBirth = distribution(randomGenerator);

    // Putting the cells into a set so I can actually find out how many 
    // UNIQUE cells are born.
    std::set<pair<int, int>> cellsToBirth;
    do {

        // Calculate which cell the random number equates to
        pair cell = determineCellFromInt(distribution(randomGenerator));
        cellsToBirth.insert(cell);

    } while (--numberOfCellsToBirth);

    cout << "Set <" + std::to_string(cellsToBirth.size()) + 
        "> alive cells." << endl;

    gameOfLife.SetCellsToAlive(
        vector<pair<int, int>>(cellsToBirth.begin(), cellsToBirth.end()));
}

std::pair<int, int> determineCellFromInt(int value){

    int x = value % GRID_DIMENSIONS.first;
    int y = static_cast<int>(value / GRID_DIMENSIONS.second);
    return pair(x, y);
}

void drawGrid(grid const & currentGrid){

    for (auto y = 0; y < currentGrid[0].size(); y++){
        for (auto x = 0; x < currentGrid.size(); x++){
                cout << " " << ((currentGrid[x][y])? "0" : "-");
        }
        cout << endl;
    }
    cout << endl;
}

