#pragma once

#include "SingletonTemplate.hpp"
#include "raylib.h"

class ResourceManager : public Singleton<ResourceManager>
{
    friend Singleton;

public:
    void LoadResources();
    void UnloadResources();

    Font GetFont() const;

private:
    Font font;
};
