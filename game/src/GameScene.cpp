#include "GameScene.hpp"
#include "singleton/Application.hpp"
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

}

void GameScene::Render()
{
    Font font = resource_manager->GetFont();
    int screen_width = Application::Get()->GetScreenWidth();
    int screen_height = Application::Get()->GetScreenHeight();

    float fontSize = font.baseSize * 3.0f;
    const char *text = "TEST";
    float textSpacing = 5.f;
    Vector2 textSize = MeasureTextEx(font, text, fontSize, textSpacing);
    DrawTextEx(font, text,
        { (screen_width * 0.5f) - (textSize.x * 0.5f),
        (screen_height * 0.5f) - (textSize.y * 0.5f) },
        fontSize, textSpacing, WHITE);
}

void GameScene::Exit()
{

}
