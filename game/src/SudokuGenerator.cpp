#include "SudokuGenerator.hpp"

#include <algorithm>
#include <cstdlib>

constexpr int UNASSIGNED = 0;

static int GenerateRandomNumber(int max)
{
    return rand() % max;
}

static int GetRandomNumber(int min, int max)
{
    return rand() % max + min;
}

SudokuGenerator::SudokuGenerator() :
    guess_number{}
{

}

SudokuGenerator::~SudokuGenerator()
{

}

void SudokuGenerator::GeneratePuzzle(int display_grid[9][9],
    int solution_grid[9][9])
{
    Randomize(display_grid);
    CreateSeed(display_grid, solution_grid);
    RemoveNumbers(display_grid);
}

void SudokuGenerator::Randomize(int grid[9][9])
{
    // randomly shuffle the guessing number array
    for (int i = 0; i < 9; i++)
    {
        guess_number[i] = i + 1;
    }
    std::_Random_shuffle1(guess_number, guess_number + 9,
        GenerateRandomNumber);

    // initialise the grid
    for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 9; x++)
        {
            grid[y][x] = UNASSIGNED;
        }
    }
}

void SudokuGenerator::RemoveNumbers(int grid[9][9])
{
    int count = 81;
    count -= GetRandomNumber(31, 28);

    while (count > 0)
    {
        int row = GenerateRandomNumber(9);
        int col = GenerateRandomNumber(9);

        // extract coordinates
        if (grid[row][col] != 0)
        {
            int temp = grid[row][col];
            grid[row][col] = UNASSIGNED;

            int check = 0;
            CountSolutions(grid, check);
            if (check != 1)
            {
                grid[row][col] = temp;
            }
            else if (check == 1)
            {
                count--;
            }
        }
    }
}

void SudokuGenerator::CountSolutions(int grid[9][9], int &solutions)
{
    int row, col;

    if (!FindUnassignedLocation(grid, row, col))
    {
        solutions++;
        return;
    }

    for (int i = 0; i < 9 && solutions < 2; i++)
    {
        if (IsSafe(grid, row, col, guess_number[i]))
        {
            grid[row][col] = guess_number[i];
            CountSolutions(grid, solutions);
        }

        grid[row][col] = UNASSIGNED;
    }
}

bool SudokuGenerator::FindUnassignedLocation(int grid[9][9], int &row,
    int &col)
{
    for (row = 0; row < 9; row++)
    {
        for (col = 0; col < 9; col++)
        {
            if (grid[row][col] == UNASSIGNED)
            {
                return true;
            }
        }
    }

    return false;
}

bool SudokuGenerator::IsSafe(int grid[9][9], int row, int col, int num)
{
    return (!UsedInRow(grid, row, num) && !UsedInCol(grid, col, num) &&
        !UsedInBox(grid, row - row % 3, col - col % 3, num));
}

bool SudokuGenerator::UsedInRow(int grid[9][9], int row, int num)
{
    for (int col = 0; col < 9; col++)
    {
        if (grid[row][col] == num)
        {
            return true;
        }
    }

    return false;
}

bool SudokuGenerator::UsedInCol(int grid[9][9], int col, int num)
{
    for (int row = 0; row < 9; row++)
    {
        if (grid[row][col] == num)
        {
            return true;
        }
    }

    return false;
}

bool SudokuGenerator::UsedInBox(int grid[9][9], int box_start_row,
    int box_start_col, int num)
{
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (grid[row + box_start_row][col + box_start_col] == num)
            {
                return true;
            }
        }
    }

    return false;
}

void SudokuGenerator::CreateSeed(int display_grid[9][9],
    int solution_grid[9][9])
{
    FillEmptyDiagonalBox(display_grid, 0);
    FillEmptyDiagonalBox(display_grid, 1);
    FillEmptyDiagonalBox(display_grid, 2);

    SolveGrid(display_grid);

    // save solution
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            solution_grid[i][j] = display_grid[i][j];
        }
    }
}

void SudokuGenerator::FillEmptyDiagonalBox(int grid[9][9], int index)
{
    int start = index * 3;
    std::_Random_shuffle1(guess_number, guess_number + 9,
        GenerateRandomNumber);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            grid[start + i][start + j] = guess_number[i * 3 + j];
        }
    }
}

bool SudokuGenerator::SolveGrid(int grid[9][9])
{
    int row, col;

    // if there is no unassigned location, return
    if (!FindUnassignedLocation(grid, row, col))
        return true; // success

    // consider digits 1 to 9
    for (int num = 0; num < 9; num++)
    {
        // if looks promising
        if (IsSafe(grid, row, col, guess_number[num]))
        {
            // make tentative assignment
            grid[row][col] = guess_number[num];

            // if success, return
            if (SolveGrid(grid))
                return true;

            // failure, unmake & try again
            grid[row][col] = UNASSIGNED;
        }
    }

    return false;
}
