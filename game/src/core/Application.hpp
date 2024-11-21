#pragma once

#include "template/SingletonTemplate.hpp"

class Scene;

class Application : public Singleton<Application>
{
    friend Singleton;

public:
    void Initialise();
    void Run();
    void Exit();

    [[nodiscard]] int GetScreenWidth() const;
    [[nodiscard]] int GetScreenHeight() const;

private:
    void Update();
    void Render();

    int screen_width;
    int screen_height;
    bool exit_app;
    Scene *scene;
};
