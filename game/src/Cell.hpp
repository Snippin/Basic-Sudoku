#pragma once

#include "raylib.h"

class Cell
{
public:
    Cell();
    ~Cell();

    void SetRectangle(Rectangle new_rectangle);
    void Render();

    bool IsHovering() const;
    void SetSelect(bool select);
    bool IsSelected() const;

private:
    Rectangle rectangle;
    bool is_selected;
};
