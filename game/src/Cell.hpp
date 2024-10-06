#pragma once

#include "raylib.h"

class Cell
{
public:
    Cell();
    ~Cell();

    void SetRectangle(Rectangle new_rectangle);
    void SetNumber(int new_number, bool given = false);
    void ValidateNumber(int correct_number);
    void Render();

    bool IsHovering() const;
    bool IsCorrect() const;
    void SetSelect(bool select);
    bool IsSelected() const;
    void SetHighlight(bool highlight);

private:
    Rectangle rectangle;
    bool is_selected;
    bool is_correct;
    bool is_given;
    bool is_highlighted;
    int number;
};
