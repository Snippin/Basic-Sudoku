#pragma once

#include "raylib.h"

class Cell
{
public:
    void SetRectangle(Rectangle new_rectangle);
    void Render();

private:
    Rectangle rectangle;
};
