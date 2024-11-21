#pragma once

#include "template/SingletonTemplate.hpp"
#include "raylib.h"

class ResourceManager : public Singleton<ResourceManager>
{
    friend Singleton;

public:
    void LoadResources();
    void UnloadResources() const;

    [[nodiscard]] Font GetFont() const;

private:
    Font font;
};
