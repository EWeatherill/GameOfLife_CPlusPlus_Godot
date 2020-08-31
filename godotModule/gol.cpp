/**
 * This implementation will be responsible for actually binding the
 * GameOfLife C++ code to the Godot GDNative API
 **/
#include <algorithm>
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
    // the coords contain two values (if not, ignore them....) 
    // and convert to std::pair
    std::vector<std::pair<int, int>> cellsCoordsAsPairs;
    std::for_each(cellsCoordinates.begin(), cellsCoordinates.end.end(),
        [&] (godot::Vector<int> coords) {
            if (coords.length() == 2){
                cellsCoordsAsPairs.push_back(std::pair(coord[0], coord[1]));
            }
        });

    golInstance.SetCellsToAlive(cellsCoordsAsPairs);
}

bool GOL::Evolve(void){
    golInstance.Evolve();
}

int GetCurrentEvolutionNumber() const { 
    return golInstance.GetCurrentEvolutionNumber();
}

godot::Vector<godot::Vector<bool>> GetGrid() const { 
    std::vector<std::vector<bool>> grid = golInstance.GetGrid();
    
    // Convert std::vector to godot::Vector
}