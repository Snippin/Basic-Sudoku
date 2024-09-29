#pragma once

#include "Scene.hpp"
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
};
