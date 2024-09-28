#pragma once

#include "SingletonTemplate.hpp"
#include "raylib.h"

class Application : public Singleton<Application>
{
    friend Singleton;

public:
    void Initialise();
    void Run();
    void Exit();

    int GetScreenWidth() const;
    int GetScreenHeight() const;

private:
    void Update();
    void Render();

    int screen_width;
    int screen_height;
    bool exit_app;

    Font font;
};