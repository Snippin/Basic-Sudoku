#pragma once

#include "template/SingletonTemplate.hpp"
#include "template/Scene.hpp"

#include <memory>


class Application : public Singleton<Application>
{
    friend Singleton;

public:
    void Initialise();
    void Run();
    void Exit();

private:
    void Update();
    void Render();

    int screen_width;
    int screen_height;
    bool exit_app;
    std::unique_ptr<Scene> scene;
};
