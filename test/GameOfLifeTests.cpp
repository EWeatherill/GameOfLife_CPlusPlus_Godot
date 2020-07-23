/**
 * Unit tests for the GameOfLife code.
 **/

#include <gtest/gtest.h>

#include <algorithm>
#include <stdexcept>
#include <vector>

#include "GameOfLife.hpp"

using std::pair;
using std::vector;

# pragma region Helper functions
int getTotalNumberOfAliveCells(vector<vector<bool>> grid){
    
    int count = 0;

    std::for_each(grid.begin(), grid.end(), [&](auto column) {
        count += std::count(column.begin(), column.end(), true);
    });

    return count;
}
#pragma endregion Helper functions

TEST(GameOfLifeTests, Constructor_BuildsEmptyGridOfCorrectSize){

    int gridWidth = 3;
    int gridHeight = 5;
    GameOfLife gameOfLife(gridWidth, gridHeight);

    auto grid = gameOfLife.GetGrid();

    // Check grid size is as expected
    EXPECT_EQ(gridWidth, grid.size());
    EXPECT_EQ(gridHeight, grid[0].size());
    
    // Check all grid cells are set to "dead" (false)
    EXPECT_EQ(0, getTotalNumberOfAliveCells(grid));
}

TEST(GameOfLifeTests, Constructor_ThrowsWhenGridHeightZero){

    int gridWidth = 7;
    int gridHeight = 0;
    try{

        GameOfLife gameOfLife(gridWidth, gridHeight);

    } catch (std::invalid_argument & ex){

        EXPECT_EQ("You can't play Game of Life with a grid of " + 
            std::to_string(gridWidth) + 
            " width and " + 
            std::to_string(gridHeight) + 
            "height!", 
            ex.what());
    }  catch (...){
        FAIL() << "The incorrect expection was thrown.";
    }  
}

TEST(GameOfLifeTests, Constructor_ThrowsWhenGridWidthZero){

    int gridWidth = 0;
    int gridHeight = 1;
    try{

        GameOfLife gameOfLife(gridWidth, gridHeight);

    } catch (std::invalid_argument & ex){

        EXPECT_EQ("You can't play Game of Life with a grid of " + 
            std::to_string(gridWidth) + 
            " width and " + 
            std::to_string(gridHeight) + 
            "height!", 
            ex.what());
    }  catch (...){
        FAIL() << "The incorrect expection was thrown.";
    }  
}

TEST(GameOfLifeTests, SetCellsToAlive_SetsValidCells){

    GameOfLife gameOfLife(3, 3);

    // Going to set 3 cells to be alive
    pair cellOne(0, 2);
    pair cellTwo(1, 1);
    pair cellThree(2, 0);

    gameOfLife.SetCellsToAlive(vector{cellOne, cellTwo, cellThree});

    // Get the grid to check the state
    auto grid = gameOfLife.GetGrid();

    // Make sure 3 cells are alive
    ASSERT_EQ(3, getTotalNumberOfAliveCells(grid));

    // Make sure the correct cells are alive
    EXPECT_TRUE(grid[cellOne.first][cellOne.second]);
    EXPECT_TRUE(grid[cellTwo.first][cellTwo.second]);
    EXPECT_TRUE(grid[cellThree.first][cellThree.second]);
}

TEST(GameOfLifeTests, SetCellsToAlive_IgnoresInvalidCellCoords){
    
    GameOfLife gameOfLife(1, 1);

    gameOfLife.SetCellsToAlive(vector{pair(2,2)});

    EXPECT_EQ(0, getTotalNumberOfAliveCells(gameOfLife.GetGrid()));
}

TEST(GameOfLifeTests, SetCellsToAlive_KeepsCellAliveIfAlreadyAlive){
    
    GameOfLife gameOfLife(1, 1);

    // Set the only cell of the grid to be alive
    gameOfLife.SetCellsToAlive(vector{pair(0, 0)});
    EXPECT_EQ(1, getTotalNumberOfAliveCells(gameOfLife.GetGrid()));

    // Set the same cell to be alive and make sure the cell stays alive
    gameOfLife.SetCellsToAlive(vector{pair(0, 0)});
    EXPECT_EQ(1, getTotalNumberOfAliveCells(gameOfLife.GetGrid()));
}

TEST(GameOfLifeTests, Evolve_IndicatesChangeOfStateGivenValidAliveCells){
    
    GameOfLife gameOfLife(3, 3);

    /**
     * Set a 3 x 3 grid with a Blicker pattern:
     *      + - + - + - +
     *      |   |   |   |
     *      + - + - + - +
     *      | A | A | A |
     *      + - + - + - +
     *      |   |   |   |
     *      + - + - + - +
     * 
     * Which will result in an oscillation between the starting 
     * state and:
     *      + - + - + - +
     *      |   | A |   |
     *      + - + - + - +
     *      |   | A |   |
     *      + - + - + - +
     *      |   | A |   |
     *      + - + - + - +
     **/ 
    gameOfLife.SetCellsToAlive(vector{pair(0, 1), pair(1, 1), pair(2, 1)});

    // Make sure Evolve() returns true to indicate grid state has changed
    // following the evolution
    EXPECT_TRUE(gameOfLife.Evolve());
}

TEST(GameOfLifeTests, Evolve_IndicatesNoChangeOfStateIfAllCellsDead){
    
    GameOfLife gameOfLife(2, 2);
    EXPECT_FALSE(gameOfLife.Evolve());
}

TEST(GameOfLifeTests, Evolve_IndicatesNoChangeOfStateIfCellsStagnated){
    
    GameOfLife gameOfLife(4, 4);

    /**
     * Set a 4 x 4 grid with a pattern:
     *      + - + - + - + - +
     *      |   |   |   |   |
     *      + - + - + - + - +
     *      |   | A | A |   |
     *      + - + - + - + - +
     *      |   | A | A |   |
     *      + - + - + - + - +
     *      |   |   |   |   |
     *      + - + - + - + - +
     * 
     * Which is a stable still lifeform and should result in no state
     * change following an evolution.
     **/ 
    gameOfLife.SetCellsToAlive(
        vector{pair(1, 1), pair(2, 1), pair(1, 2), pair(2, 2)});
    
    EXPECT_FALSE(gameOfLife.Evolve());
}

TEST(GameOfLifeTests, GetCurrentEvolutionNumber_IfNoEvolutionsUndertaken){
    
    GameOfLife GameOfLife(1, 1);
    EXPECT_EQ(0, GameOfLife.GetCurrentEvolutionNumber());
}

TEST(GameOfLifeTests, GetCurrentEvolutionNumber_AfterEvolutionsOccured){
    
    GameOfLife gameOfLife(3, 3);

    // Using a Blinker oscillating pattern
    gameOfLife.SetCellsToAlive(vector{pair(0, 1), pair(1, 1), pair(2, 1)});

    // Evolve 5 times
    for (int i = 0; i < 5; i++) gameOfLife.Evolve();

    EXPECT_EQ(5, gameOfLife.GetCurrentEvolutionNumber());
}