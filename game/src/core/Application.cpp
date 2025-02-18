#include "Application.hpp"

#include "scene/MainMenuScene.hpp"
#include "scene/GameScene.hpp"
#include "ResourceManager.hpp"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "raylib.h"

#include <memory>

void Application::Initialise()
{
    screen_width = 1000;
    screen_height = 750;

    // initialise window
    InitWindow(screen_width, screen_height, "Basic Sudoku");
    SetExitKey(KEY_NULL);
    InitAudioDevice();
    SetTargetFPS(60);

    // initialise variables
    exit_app = false;

    ResourceManager::Get()->LoadResources();
}

void Application::Run()
{
    scene = std::make_unique<MainMenuScene>();
    scene->Enter();

    while (!WindowShouldClose() && !exit_app)
    {
        Update();
        Render();
    }
}

void Application::Exit()
{
    if (scene != nullptr)
    {
        scene->Exit();
    }

    ResourceManager::Get()->UnloadResources();

    CloseAudioDevice();
    CloseWindow();
}

void Application::Update()
{
    scene->Update();
}

void Application::Render()
{
    BeginDrawing();
    ClearBackground(BLACK);
    scene->Render();
    EndDrawing();
}
