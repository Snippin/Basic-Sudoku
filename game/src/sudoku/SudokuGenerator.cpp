#include "SudokuGenerator.hpp"

#include "DifficultyLevel.hpp"

#include <algorithm>
#include <random>

constexpr int UNASSIGNED = 0;

static int GetRandomNumber(int max, int min = 0)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution dist(min, max - 1);
    return dist(gen);
}

SudokuGenerator::SudokuGenerator() :
    guess_number{}
{

}

void SudokuGenerator::GeneratePuzzle(int display_grid[9][9],
    int solution_grid[9][9], DifficultyLevel difficulty)
{
    Randomize(display_grid);
    CreateSeed(display_grid, solution_grid);
    RemoveNumbers(display_grid, difficulty);
}

void SudokuGenerator::Randomize(int grid[9][9])
{
    // Randomly shuffle the guessing number array
    for (int i = 0; i < 9; i++)
    {
        guess_number[i] = i + 1;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(guess_number.begin(), guess_number.end(), gen);

    // Initialise the grid
    for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 9; x++)
        {
            grid[y][x] = UNASSIGNED;
        }
    }
}

void SudokuGenerator::RemoveNumbers(int grid[9][9],
    DifficultyLevel difficulty)
{
    int count = 81;

    switch (difficulty)
    {
    case DifficultyLevel::EASY:
        count -= GetRandomNumber(35, 32);
        break;

    case DifficultyLevel::MEDIUM:
        count -= GetRandomNumber(31, 28);
        break;

    case DifficultyLevel::HARD:
        count -= GetRandomNumber(27, 22);
        break;

    default:
        return;
    }

    while (count > 0)
    {
        int row = GetRandomNumber(9);
        int col = GetRandomNumber(9);

        // Extract coordinates
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
    int row;
    int col;

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
    int &col) const
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

bool SudokuGenerator::IsSafe(int grid[9][9], int row, int col, int num) const
{
    return (!UsedInRow(grid, row, num) && !UsedInCol(grid, col, num) &&
        !UsedInBox(grid, row - row % 3, col - col % 3, num));
}

bool SudokuGenerator::UsedInRow(int grid[9][9], int row, int num) const
{
    return std::any_of(std::begin(grid[row]), std::end(grid[row]), [&](int cell)
    {
        return cell == num;
    });
}

bool SudokuGenerator::UsedInCol(int grid[9][9], int col, int num) const
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
    int box_start_col, int num) const
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

    // Save solution
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            solution_grid[i][j] = display_grid[i][j];
        }
    }
}

void SudokuGenerator::FillEmptyDiagonalBox(int grid[9][9], int index) const
{
    int start = index * 3;

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
    int row;
    int col;

    // If there is no unassigned location, return
    if (!FindUnassignedLocation(grid, row, col))
    {
        // Success
        return true;
    }

    // Consider digits 1 to 9
    if (std::any_of(std::begin(guess_number), std::end(guess_number),
        [&](int num)
        {
            // If it looks promising
            if (IsSafe(grid, row, col, num))
            {
                // Make tentative assignment
                grid[row][col] = num;

                // If success, return
                if (SolveGrid(grid))
                    return true;

                // Failure, unmake & try again
                grid[row][col] = UNASSIGNED;
            }

            return false;
        }))
    {
        return true;
    }

    return false;
}
