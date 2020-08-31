/**
 * This implementation will be responsible for actually binding the
 * GameOfLife C++ code to the Godot GDNative API
 **/
#include <GameOfLife.hpp>
#include <vector>

#include "gol.hpp"

GameOfLife golInstance;

GOL::GOL(int gridWidthInCells, int gridHeightInCells){
    golInstance = GameOfLife(gridWidthInCells, gridHeightInCells);
}

void GOL::SetCellsToAlive(
    godot::Vector<godot::Vector<int>> const cellsCoordinates){

    // Godot doesn't support the C++ Pair container so check
    // the coords contain two values and convert to std::pair

    std::vector<std::pair<int, int>> cellsCoordsAsPairs;

    golInstance.SetCellsToAlive(cellsCoordsAsPairs);
}

bool GOL::Evolve(void){
    golInstance.Evolve();
}

int GetCurrentEvolutionNumber() const { 
    return golInstance.GetCurrentEvolutionNumber();
}

godot::Vector<godot::Vector<bool>> GetGrid() const { 



}