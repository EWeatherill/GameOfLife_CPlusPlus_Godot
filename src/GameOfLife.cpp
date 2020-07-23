#include <algorithm>
#include <stdexcept>

#include "GameOfLife.hpp"

using std::for_each;
using std::vector;

// Make an alias for the 2D vector that represents the grid
using gridType = vector<vector<bool>>;

GameOfLife::GameOfLife(int gridWidth, int gridHeight){

    if (gridWidth == 0 || gridHeight == 0){
        throw std::invalid_argument(
            "You can't play Game of Life with a grid of " + 
            std::to_string(gridWidth) + 
            " width and " + 
            std::to_string(gridHeight) + 
            "height!");
    }

    grid = vector(gridWidth, vector(gridHeight, false));
}

void GameOfLife::SetCellsToAlive(
    vector<std::pair<int, int>> const cellsCoordinates){

    for_each(cellsCoordinates.begin(), cellsCoordinates.end(), 
        [&] (std::pair<int, int> coord) {

            // Only try to set cells to alive if the coords are inside the
            // bounds of the grid
            if ( coord.first < grid.size() && coord.second < grid[0].size()){
                grid[coord.first][coord.second] = true;
            }
        });    
}

bool GameOfLife::Evolve(void){

    // If the temp grid has yet to be used, initialise it as an empty grid
    if (!temporary_Grid.has_value())
        temporary_Grid = vector(grid.size(), vector(grid[0].size(), false));

    bool cellsChanged = false;

    for (auto x = 0; x < grid.size(); x++){
        for (auto y = 0; y < grid[0].size(); y++){

            bool cellState = grid[x][y];
            int livingNeighboursCount = 
                getNumberOfAliveNeighbours(grid, x, y);

            if (cellState && 
                (livingNeighboursCount < 2 || livingNeighboursCount > 3)){

                cellState = false;
                cellsChanged = true;
            } else if (!cellState && livingNeighboursCount == 3){
                cellState = true;
                cellsChanged = true;
            }

            temporary_Grid.value()[x][y] = cellState;
        }
    }

    if (cellsChanged){
        std::swap(grid, temporary_Grid.value());
        number_Of_Evolutions_So_Far++;
    }

    return cellsChanged;
}

int GameOfLife::getNumberOfAliveNeighbours(
    gridType const & grid,
    size_t xCoord,
    size_t yCoord) const {

    int numberOfAliveNeighbours = 0;

    bool hasNorth = false;
    bool hasEast = false;
    bool hasSouth = false;
    bool hasWest = false;

    // Check North
    if (yCoord > 0) {
        hasNorth = true;
        if (grid[xCoord][yCoord - 1]) numberOfAliveNeighbours++;
    }

    // Check East
    if (xCoord < grid.size() - 1){
        hasEast = true;
        if (grid[xCoord + 1][yCoord]) numberOfAliveNeighbours++;
    }

    // Check South
    if (yCoord < grid[xCoord].size() - 1){
        hasSouth = true;
        if (grid[xCoord][yCoord + 1]) numberOfAliveNeighbours++;
    }

    // Check West
    if (xCoord > 0){
        hasWest = true;
        if (grid[xCoord - 1][yCoord]) numberOfAliveNeighbours++;
    }

    // Check the diagonal neighbours if necessary
    if (hasNorth && hasEast && grid[xCoord + 1][yCoord - 1]) 
        numberOfAliveNeighbours++;
    if (hasSouth && hasEast && grid[xCoord + 1][yCoord + 1]) 
        numberOfAliveNeighbours++;
    if (hasSouth && hasWest && grid[xCoord - 1][yCoord + 1]) 
        numberOfAliveNeighbours++;
    if (hasNorth && hasWest && grid[xCoord - 1][yCoord - 1]) 
        numberOfAliveNeighbours++;

    return numberOfAliveNeighbours;
}