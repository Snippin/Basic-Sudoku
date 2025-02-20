#include "MainMenuScene.hpp"

#include "raylib.h"
#include "core/ResourceManager.hpp"
#include "core/Application.hpp"
#include "core/raygui.h"
#include "sudoku/DifficultyLevel.hpp"
#include "SceneType.hpp"

void MainMenuScene::Update()
{
    if (IsKeyPressed(KEY_ESCAPE))
    {
        Application::Get()->Quit();
    }
}

void MainMenuScene::Render()
{
    int screen_width = GetScreenWidth();
    int screen_height = GetScreenHeight();
    Vector2 screen_half = { static_cast<float>(screen_width) * 0.5f,
        static_cast<float>(screen_height) * 0.5f };

    Vector2 button_size = { 200, 50 };
    float button_height = screen_half.y - (button_size.y * 3.5f);
    Vector2 button_position = {
        screen_half.x - (button_size.x * 0.5f), button_height};
    float button_space = button_size.y * 1.5f;

    if (GuiButton({ button_position.x, button_position.y, button_size.x,
        button_size.y }, "Play Easy"))
    {
        HitPlayButton(DifficultyLevel::EASY);
    }

    button_position.y += button_space;
    if (GuiButton({ button_position.x, button_position.y, button_size.x,
    button_size.y }, "Play Medium"))
    {
        HitPlayButton(DifficultyLevel::MEDIUM);
    }

    button_position.y += button_space;
    if (GuiButton({ button_position.x, button_position.y, button_size.x,
    button_size.y }, "Play Hard"))
    {
        HitPlayButton(DifficultyLevel::HARD);
    }

    button_position.y += button_space;
    if (GuiButton({ button_position.x, button_position.y, button_size.x,
        button_size.y }, "Quit"))
    {
        Application::Get()->Quit();
    }
}

void MainMenuScene::HitPlayButton(DifficultyLevel difficulty)
{
    ResourceManager::Get()->SetDifficulty(difficulty);
    Application::Get()->ChangeScene(SceneType::Game);
}
