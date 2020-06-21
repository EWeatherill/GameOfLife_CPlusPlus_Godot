#pragma once

#include <vector>

/**
This class is responsible for handling the grid of cells that can
evolve through generations following Conway's Game of Life rules.
**/
class GameOfLife{

    private:
        std::pair gridSize;
        std::vector<std::vector<bool>> grid;
        std::vector<std::vector<bool>> temporaryGrid;

    public:

        /**
        Create a new Game of Life instance with a grid of cells
        with the dimensions given.  All cells within the grid are
        set to false (dead) by default.

        @param gridWith: the number of cells making up the width
               of the grid
        @param gridHeight: the number of cells making up the
               height of the grid
        **/
        GameOfLife(int gridWidth, int gridHeight);

        /**
        TODO:

        How do I want to handle toggling cell state when the user is selecting
            the initial cells on the starting grid?
        Do I want specific methods to "SetCellToDead" and "SetCellToAlive"?
        It would be good to have methods that can be used during the
             evolution.
        Do I want to change cell state one at a time or variable numbers
             of them at once?

        **/
        void ToggleCellState(std::pair<int, int> cellCoordinates);


};
