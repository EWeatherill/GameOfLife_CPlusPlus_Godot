/**
 * Unit tests for the GameOfLife code.
 **/

#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

#include "GameOfLife.hpp"

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

TEST(GameOfLifeTests, SetCellsToAlive_SetsValidCells){

    GameOfLife gameOfLife(3, 3);

    // Going to set 3 cells to be alive
    std::pair cellOne(0, 2);
    std::pair cellTwo(1, 1);
    std::pair cellThree(2, 0);

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
    ASSERT_TRUE(false) << "Not implemented";
}

TEST(GameOfLifeTests, SetCellsToAlive_KeepsCellAliveIfAlreadyALive){
    ASSERT_TRUE(false) << "Not implemented";
}

TEST(GameOfLifeTests, Evolve_IndicatesChangeOfStateGivenValidAliveCells){
    ASSERT_TRUE(false) << "Not implemented";
}

TEST(GameOfLifeTests, Evolve_IndicatesNoChangeOfStateIfCellsStagnated){
    ASSERT_TRUE(false) << "Not implemented";
}

TEST(GameOfLifeTests, GetCurrentEvolutionNumber_IfNoEvolutionsUndertaken){
    ASSERT_TRUE(false) << "Not implemented";
}

TEST(GameOfLifeTests, GetCurrentEvolutionNumber_AfterEvolvutionOccured){
    ASSERT_TRUE(false) << "Not implemented";
}