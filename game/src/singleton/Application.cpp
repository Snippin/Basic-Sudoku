#include "Application.hpp"
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
    font = LoadFont("resources/mecha.png");
}

void Application::Run()
{
    while (!WindowShouldClose() && !exit_app)
    {
        Update();
        Render();
    }
}

void Application::Exit()
{
    UnloadFont(font);
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
}

void Application::Render()
{
    BeginDrawing();
    ClearBackground(BLACK);

    float fontSize = font.baseSize * 3.0f;
    const char *text = "TEST";
    float textSpacing = 5.f;
    Vector2 textSize = MeasureTextEx(font, text, fontSize, textSpacing);
    DrawTextEx(font, text,
        { (screen_width * 0.5f) - (textSize.x * 0.5f),
        (screen_height * 0.5f) - (textSize.y * 0.5f) },
        fontSize, textSpacing, WHITE);

    EndDrawing();
}
