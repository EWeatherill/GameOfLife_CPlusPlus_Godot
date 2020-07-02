#pragma once

#include <vector>

/**
 * This class is responsible for handling the grid of cells that can
 * evolve through generations, following Conway's Game of Life rules.
 **/
class GameOfLife{

    private:
        std::pair<int, int> grid_Size;
        std::vector<std::vector<bool>> grid;
        std::vector<std::vector<bool>> temporary_Grid;
        int number_Of_Evolutions_So_Far = 0;

        /**
         * Get the number of alive cells surrounding the cell at the given
         * coordinates.
         *
         * @param  grid:   the grid to interrogate
         * @param  xCoord: the x coordinate (zero-based) of the cell to check
         * @param  yCoord: the y coordinate (zero-based) of the cell to check
         * @return an int of the number of alive cells surrounding the
         *         cell at the coordinates given
         **/
        int getNumberOfAliveNeighbours(
            std::vector<std::vector<bool>> const & grid, 
            size_t xCoord, 
            size_t yCoord) const;

    public:

        /**
         * Create a new Game of Life instance with a grid of cells
         * with the dimensions given.  The grid size is fixed
         * for the lifetime of the object.  All cells within the grid are
         * false (dead) by default.
         *
         * @param gridWidthInCells: the number of cells making up the width
         *        of the grid
         * @param gridHeightInCells: the number of cells making up the
         *        height of the grid
         **/
        GameOfLife(int gridWidthInCells, int gridHeightInCells);

        /**
         * Set the given list of cells to "alive" (true) state.  The
         * coordinates are zero-based {column, row}.
         *
         * If any of the coordinates fall outside the range of the grid
         * they will be ignored.
         *
         * @param cellsCoordinates: a vector of std::pair<int, int>
         *        representing the coordinates {column, row} of the cell
         *        to set as "alive"
         **/
        void SetCellsToAlive(
            std::vector<std::pair<int, int>> const cellsCoordinates);

        /**
         * Evolve through one generation following Conway's Game of Life
         * rules.
         *
         * @return a boolean if grid state changed (i.e. a cell "died" or
         *         was "born")
         **/
        bool Evolve(void);

        /**
         * Get the number of evolutons which have occured so far.
         *
         * @return an int representing the number of evolutions that
         *         have occured so far
         **/
        int GetCurrentEvolutionNumber() const { 
            return number_Of_Evolutions_So_Far; }

        /**
         * Get the current state of the grid.
         *
         * @return a vector of boolean vectors.  The outermost vector
         *         represents the x coordinate/column index.  The innermost 
         *         vector represents the y coordinate/row index.
         **/
        std::vector<std::vector<bool>> GetGrid() const { 
            return grid; }
};
