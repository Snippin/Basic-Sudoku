#pragma once

#include "template/SingletonTemplate.hpp"
#include "sudoku/DifficultyLevel.hpp"
#include "raylib.h"

class ResourceManager : public Singleton<ResourceManager>
{
    friend Singleton;

public:
    void LoadResources();
    void UnloadResources() const;

    Font GetFont() const;
    void SetDifficulty(DifficultyLevel new_difficulty);
    DifficultyLevel GetDifficulty() const;

private:
    Font font;
    DifficultyLevel difficulty;
};
