#include "ResourceManager.hpp"

#include <raylib.h>

#define FONT(font_name) ("resources/fonts/" font_name)

void ResourceManager::LoadResources()
{
    font = LoadFont(FONT("pixel_play.png"));
}

void ResourceManager::UnloadResources() const
{
    UnloadFont(font);
}

Font ResourceManager::GetFont() const
{
    return font;
}

void ResourceManager::SetDifficulty(DifficultyLevel new_difficulty)
{
    difficulty = new_difficulty;
}

DifficultyLevel ResourceManager::GetDifficulty() const
{
    return difficulty;
}
