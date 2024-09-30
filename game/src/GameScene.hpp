#pragma once

#include "Scene.hpp"
#include "Cell.hpp"
#include "SudokuGenerator.hpp"

class GameScene : public Scene
{
public:
    GameScene();
    ~GameScene();

    void Enter() override;
    void Update() override;
    void Render() override;
    void Exit() override;

private:
    void SelectCell(int x, int y);

    SudokuGenerator generator;
    int display_grid[9][9];
    int solution_grid[9][9];


    float timer;
    Cell cells[9][9];
    int selected_x;
    int selected_y;
};
