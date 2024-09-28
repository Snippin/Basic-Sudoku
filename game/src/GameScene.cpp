#include "GameScene.hpp"
#include "singleton/Application.hpp"
#include "raylib.h"

GameScene::GameScene() : timer{ 0 }, font{ 0 }
{

}

GameScene::~GameScene()
{

}

void GameScene::Enter()
{
    font = LoadFont("resources/mecha.png");
}

void GameScene::Update()
{
}

void GameScene::Render()
{
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
    UnloadFont(font);
}
