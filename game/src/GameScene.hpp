#pragma once

#include "template/Scene.hpp"
#include "sudoku/Cell.hpp"
#include "sudoku/SudokuGenerator.hpp"
#include "sudoku/DifficultyLevel.hpp"
#include "raylib.h"

class GameScene : public Scene
{
public:
    GameScene();

    void Enter() override;
    void Update() override;
    void Render() override;

private:
    void RenderGrid();
    void RenderEnd();

    void InitialiseGridPositions();
    void StartGame();
    void SelectCell(int x, int y);
    void SetCellNumber(int number);
    void HighlightRowCol(bool highlight);
    void CheckBoard();
    void EndGame();

    SudokuGenerator generator;
    DifficultyLevel difficulty_level;
    int display_grid[9][9];
    int solution_grid[9][9];

    float timer;
    Cell cells[9][9];
    Rectangle regions[9];
    int selected_x;
    int selected_y;
    bool note_placing_mode;

    int remaining_space;
    bool game_over;
};
