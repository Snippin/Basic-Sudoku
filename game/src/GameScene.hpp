#pragma once

#include "Scene.hpp"
#include "Cell.hpp"
#include "raylib.h"

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
    float timer;
    Cell cells[9][9];
};
