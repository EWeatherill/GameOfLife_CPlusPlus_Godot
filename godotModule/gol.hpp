/**
 * Following the Godot documentation for binding to external libraries
 * in an effort to not alter the original GameOfLife.hpp/cpp files.
 * 
 * This file should provide the wrapper for the GameOfLife C++ implementation
 * and will be use to link that to Godot via GDNative.
 * 
 * Types should probably refer to Godot supported containers such as
 * Vector defined in Godot core code.
 **/

#pragma once

#include "core/reference.h"
#include "core/vector.h"

class GOL : public reference {
    GDCLASS(GOL, Reference);

    protected:
        static void _bind_methods();

    public:
        /**
         * Binding for GameOfLife constructor
         **/
        GOL(int gridWidthInCells, int gridHeightInCells);

        /**
         * Binding for GameOfLife SetCellsToAlive().
         **/
        void SetCellsToAlive(
            godot::Vector<godot::Vector<int>> const cellsCoordinates);

        /**
         * Binding for GameOfLife Evolve()
         **/
        bool Evolve(void);

        /**
         * Binding for GameOfLife GetCurrentEvolutionNumber()
         **/
        int GetCurrentEvolutionNumber() const;

        /**
         * Binding for GameOfLife GetGrid()
         **/
        godot::Vector<godot::Vector<bool>> GetGrid() const;

};