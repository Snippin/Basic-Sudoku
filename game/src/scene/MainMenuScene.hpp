#pragma once

#include "template/Scene.hpp"

enum class DifficultyLevel;

class MainMenuScene : public Scene
{
public:
    MainMenuScene() = default;

    void Update() override;
    void Render() override;

private:
    void HitPlayButton(DifficultyLevel difficulty);
};
