#include "ResourceManager.hpp"

#define FONT(font_name) ("resources/fonts/" font_name)

void ResourceManager::LoadResources()
{
    font = LoadFont(FONT("pixel_play.png"));
}

void ResourceManager::UnloadResources()
{
    UnloadFont(font);
}

Font ResourceManager::GetFont() const
{
    return font;
}
