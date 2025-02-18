#pragma once

#include "template/Scene.hpp"

class MainMenuScene : public Scene
{
public:
    MainMenuScene() = default;

    void Update() override;
    void Render() override;
};
