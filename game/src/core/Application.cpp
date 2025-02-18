#include "Application.hpp"

#include "ResourceManager.hpp"
#include "scene/GameScene.hpp"
#include "scene/MainMenuScene.hpp"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "raylib.h"

#include <memory>
#include <SceneType.hpp>

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

void Application::ChangeScene(SceneType sceneType)
{
    if (scene != nullptr)
    {
        scene->Exit();
        scene.reset();
    }

    switch (sceneType)
    {
    case SceneType::MainMenu:
        scene = std::make_unique<MainMenuScene>();
        break;

    case SceneType::Game:
        scene = std::make_unique<GameScene>();
        break;

    default:
        return;
    }

    scene->Enter();
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
