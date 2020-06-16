/**
May 2020

Putting my newly aquired C++17 knowledge to use with an implementation of
Conway's Game of Life.

Update: I tried with a single array to hold all grid values but it was starting
to get very complicated, and therefore error prone, when trying to determine
each cells neighbours.  So I am changing it to use a 2D array
which has it's own mess but hopefully will be less confusing for getting
neighbour state.

TODO: see if I can get std::fill and std::for_each to work on the 2D array
instead of having raw for loops.

TODO: user defined grid size and max number of evolutions; will need to move
away for using an std::array.
**/

#include <algorithm>
#include <vector>
#include <iostream>
#include <random>
#include <string>

using std::vector;
using std::cout;
using std::endl;

// Properties to change for fun.
std::pair constexpr GRID_DIMENSIONS{ 15, 15 };
int constexpr MAX_EVOLUTIONS = 30;

// Make an alias for the 2D vector that represents the grid
using grid = vector<vector<bool>>;

// Forward declarations
void setGridToDead(grid & currentGrid);
void setRandomAliveCells(grid & currentGrid);
std::pair<int, int> determineCellFromInt(int value);
bool evolve(grid const & currentGrid, grid & generationGrid);
int getNumberOfAliveNeighbours(grid const & currentGrid, size_t xCoord, size_t yCoord);
void drawGrid(grid const & currentGrid);


int main()
{

    grid currentGrid(GRID_DIMENSIONS.first, vector<bool>(GRID_DIMENSIONS.second, false));
    setGridToDead(currentGrid);
    setRandomAliveCells(currentGrid);

    cout << "Starting grid: " << endl;
    drawGrid(currentGrid);

    // Need another grid to hold the next generation of cells without altering
    // the current grid state
    grid generationGrid(GRID_DIMENSIONS.first, vector<bool>(GRID_DIMENSIONS.second, false));

    int numberOfEvolutions = 0;
    while (numberOfEvolutions < MAX_EVOLUTIONS && evolve(currentGrid, generationGrid)){

        cout << "Evolution " << ++numberOfEvolutions << endl;
        drawGrid(generationGrid);

        std::swap(currentGrid, generationGrid);
    }

    cout << "Evolution ended" << endl;
    return 0;
}


void setGridToDead(grid & currentGrid){

    for (size_t x = 0; x < currentGrid.size(); x++){
        for (size_t y = 0; y < currentGrid[x].size(); y++){
                currentGrid[x][y] = false;
        }
    }
}


void setRandomAliveCells(grid & currentGrid){

    std::random_device randomDevice;
    std::mt19937 randomGenerator(randomDevice());
    std::uniform_int_distribution<int> distribution(0, GRID_DIMENSIONS.first * GRID_DIMENSIONS.second - 1);

    int numberOfCellsToBirth = distribution(randomGenerator);
    int numberOfUniqueCellsAlive = 0;
    do {

        // Calculate which cell the random number equates to
        std::pair cell = determineCellFromInt(distribution(randomGenerator));

        // Set the grid cell to be alive if it is not already
        if (currentGrid[cell.first][cell.second] == false){
            currentGrid[cell.first][cell.second] = true;
            numberOfUniqueCellsAlive++;
        }
    } while (--numberOfCellsToBirth);

    cout << "Set <" + std::to_string(numberOfUniqueCellsAlive) + "> alive cells." << endl;
}


std::pair<int, int> determineCellFromInt(int value){

    int x = value % GRID_DIMENSIONS.first;
    int y = static_cast<int>(value / GRID_DIMENSIONS.second);
    return std::pair(x, y);
}


bool evolve(grid const & currentGrid, grid & generationGrid){

    bool cellsChanged = false;

    for (size_t x = 0; x < currentGrid.size(); x++){
        for (size_t y = 0; y < currentGrid[0].size(); y++){

            bool cellState = currentGrid[x][y];
            int livingNeighboursCount = getNumberOfAliveNeighbours(currentGrid, x, y);

            if (cellState && (livingNeighboursCount < 2 || livingNeighboursCount > 3)){
                cellState = false;
                cellsChanged = true;
            } else if (!cellState && livingNeighboursCount == 3){
                cellState = true;
                cellsChanged = true;
            }

            generationGrid[x][y] = cellState;
        }
    }

    return cellsChanged;
}


int getNumberOfAliveNeighbours(grid const & currentGrid, size_t xCoord, size_t yCoord){

    int numberOfAliveNeighbours = 0;

    bool hasNorth = false;
    bool hasEast = false;
    bool hasSouth = false;
    bool hasWest = false;

    // Check North
    if (yCoord > 0 && yCoord < currentGrid[xCoord].size()) {
        hasNorth = true;
        if (currentGrid[xCoord][yCoord - 1]) numberOfAliveNeighbours++;
    }

    // Check East
    if (xCoord >= 0 && xCoord < currentGrid.size() - 1){
        hasEast = true;
        if (currentGrid[xCoord + 1][yCoord]) numberOfAliveNeighbours++;
    }

    // Check South
    if (yCoord >= 0 && yCoord < currentGrid[xCoord].size() - 1){
        hasSouth = true;
        if (currentGrid[xCoord][yCoord + 1]) numberOfAliveNeighbours++;
    }

    // Check East
    if (xCoord > 0 && xCoord < currentGrid.size()){
        hasWest = true;
        if (currentGrid[xCoord - 1][yCoord]) numberOfAliveNeighbours++;
    }

    // Check the diagnol neighbours if necessary
    if (hasNorth && hasEast && currentGrid[xCoord + 1][yCoord - 1]) numberOfAliveNeighbours++;
    if (hasSouth && hasEast && currentGrid[xCoord + 1][yCoord + 1]) numberOfAliveNeighbours++;
    if (hasSouth && hasWest && currentGrid[xCoord - 1][yCoord + 1]) numberOfAliveNeighbours++;
    if (hasNorth && hasWest && currentGrid[xCoord - 1][yCoord - 1]) numberOfAliveNeighbours++;

    return numberOfAliveNeighbours;
}


void drawGrid(grid const & currentGrid){

    for (size_t y = 0; y < currentGrid[0].size(); y++){
        for (size_t x = 0; x < currentGrid.size(); x++){
                cout << " " << ((currentGrid[x][y])? "0" : "-");
        }
        cout << endl;
    }
    cout << endl;
}

