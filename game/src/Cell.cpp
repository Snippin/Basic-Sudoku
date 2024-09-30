#include "Cell.hpp"

#include "singleton/ResourceManager.hpp"

#include <string>

Cell::Cell() : rectangle{}, is_selected{}, number{ 0 }
{

}

Cell::~Cell()
{

}

void Cell::SetRectangle(Rectangle new_rectangle)
{
    rectangle = new_rectangle;
}

void Cell::SetNumber(int new_number)
{
    number = new_number;
}

void Cell::Render()
{
    Font font = ResourceManager::Get()->GetFont();
    float font_size = font.baseSize * 3.f;
    float text_spacing = 4.f;

    if (is_selected)
    {
        DrawRectangleLinesEx(rectangle, 1.5f, YELLOW);
    }
    else
    {
        DrawRectangleLinesEx(rectangle, 1, DARKGRAY);
    }

    if (number != 0)
    {
        Vector2 textSize = MeasureTextEx(font, std::to_string(number).c_str(),
            font_size, text_spacing);
        Vector2 textPos = {
            rectangle.x + rectangle.width * 0.5f - textSize.x * 0.5f,
            rectangle.y + rectangle.height * 0.05f
        };
        Color textColor = WHITE;
        DrawTextEx(font, std::to_string(number).c_str(), textPos, font_size,
            text_spacing, textColor);
    }
}

bool Cell::IsHovering() const
{
    return CheckCollisionPointRec(GetMousePosition(), rectangle);
}

void Cell::SetSelect(bool select)
{
    is_selected = select;
}

bool Cell::IsSelected() const
{
    return is_selected;
}
