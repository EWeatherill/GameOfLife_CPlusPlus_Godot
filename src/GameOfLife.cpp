#include "GameOfLife.hpp"

using std::vector;

GameOfLife::GameOfLife(int gridWidth, int gridHeight){

    grid = vector{vector{false}};
}

void GameOfLife::SetCellsToAlive(
    vector<std::pair<int, int>> const cellsCoordinates){
    
}

bool GameOfLife::Evolve(void){
    return false;
}

int GameOfLife::getNumberOfAliveNeighbours(
    vector<vector<bool>> const & grid,
    size_t xCoord,
    size_t yCoord) const {

    return 0;
}