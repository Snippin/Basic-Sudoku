#include "GameScene.hpp"
#include "singleton/ResourceManager.hpp"

#include "raylib.h"

namespace
{
    ResourceManager *resource_manager = ResourceManager::Get();
}

GameScene::GameScene() : timer{ 0 }
{

}

GameScene::~GameScene()
{

}

void GameScene::Enter()
{

}

void GameScene::Update()
{
    timer += GetFrameTime();
}

void GameScene::Render()
{
    int screen_width = GetScreenWidth();
    int screen_height = GetScreenHeight();
    Font font = resource_manager->GetFont();
    float font_size = font.baseSize * 3.f;
    float text_spacing = 4.f;

    // timer
    const char *text =
        TextFormat("%02d:%02d", (int)timer / 60, (int)timer % 60);
    Vector2 text_size = MeasureTextEx(font, text, font_size, text_spacing);
    Vector2 textPos =
    { screen_width * 0.5f - (text_size.x * 0.5f), font_size * 0.5f };
    DrawTextEx(font, text, textPos, font_size, text_spacing, WHITE);
}

void GameScene::Exit()
{

}
