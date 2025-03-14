#pragma once

#include "DifficultyLevel.hpp"

#include <array>

class SudokuGenerator
{
public:
    SudokuGenerator();
    ~SudokuGenerator() = default;

    void GeneratePuzzle(int display_grid[9][9], int solution_grid[9][9],
        DifficultyLevel difficulty);

private:
    void Randomize(int grid[9][9]);

    void RemoveNumbers(int grid[9][9], DifficultyLevel difficulty);
    void CountSolutions(int grid[9][9], int &solutions);
    bool FindUnassignedLocation(int grid[9][9], int &row, int &col) const;
    bool IsSafe(int grid[9][9], int row, int col, int num) const;
    bool UsedInRow(int grid[9][9], int row, int num) const;
    bool UsedInCol(int grid[9][9], int col, int num) const;
    bool UsedInBox(int grid[9][9], int box_start_row, int box_start_col,
        int num) const;

    void CreateSeed(int display_grid[9][9], int solution_grid[9][9]);
    void FillEmptyDiagonalBox(int grid[9][9], int index) const;
    bool SolveGrid(int grid[9][9]);

    std::array<int, 9> guess_number;
};
