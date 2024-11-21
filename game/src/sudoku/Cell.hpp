#pragma once

#include "raylib.h"

class Cell
{
public:
    Cell();
    ~Cell() = default;

    void SetRectangle(Rectangle new_rectangle);
    void SetNumber(int new_number, bool given = false);
    void ValidateNumber(int correct_number);
    void Render();

    [[nodiscard]] bool IsHovering() const;
    [[nodiscard]] bool IsCorrect() const;
    void SetSelect(bool select);
    [[nodiscard]] bool IsSelected() const;
    void SetHighlight(bool highlight);
    void SetNote(int number_to_set);

private:
    Rectangle rectangle;
    bool is_selected;
    bool is_correct;
    bool is_given;
    bool is_highlighted;
    int number;
    bool notes[9];
};
