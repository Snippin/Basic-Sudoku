#pragma once

#include "template/SingletonTemplate.hpp"
#include "template/Scene.hpp"

#include <memory>

enum class SceneType;

class Application : public Singleton<Application>
{
    friend Singleton;

public:
    void Initialise();
    void Run();
    void Exit();

    void Quit();
    void ChangeScene(SceneType sceneType);

private:
    void Update();
    void Render();

    int screen_width = 0;
    int screen_height= 0;
    bool exit_app = false;
    std::unique_ptr<Scene> scene;
};
