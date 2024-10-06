#pragma once

#include "DifficultyLevel.hpp"

class SudokuGenerator
{
public:
    SudokuGenerator();
    ~SudokuGenerator();

    void GeneratePuzzle(int display_grid[9][9], int solution_grid[9][9],
        DifficultyLevel difficulty);

private:
    void Randomize(int grid[9][9]);

    void RemoveNumbers(int grid[9][9], DifficultyLevel difficulty);
    void CountSolutions(int grid[9][9], int &solutions);
    bool FindUnassignedLocation(int grid[9][9], int &row, int &col);
    bool IsSafe(int grid[9][9], int row, int col, int num);
    bool UsedInRow(int grid[9][9], int row, int num);
    bool UsedInCol(int grid[9][9], int col, int num);
    bool UsedInBox(int grid[9][9], int box_start_row, int box_start_col,
        int num);

    void CreateSeed(int display_grid[9][9], int solution_grid[9][9]);
    void FillEmptyDiagonalBox(int grid[9][9], int index);
    bool SolveGrid(int grid[9][9]);

    int guess_number[9];
};
