#include "Application.hpp"
#include "GameScene.hpp"
#include "raylib.h"

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
}

void Application::Run()
{
    scene = new GameScene();
    scene->Enter();

    while (!WindowShouldClose() && !exit_app)
    {
        Update();
        Render();
    }
}

void Application::Exit()
{
    if (scene != NULL)
    {
        scene->Exit();
        delete scene;
    }

    CloseAudioDevice();
    CloseWindow();
}

int Application::GetScreenWidth() const
{
    return screen_width;
}

int Application::GetScreenHeight() const
{
    return screen_height;
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
