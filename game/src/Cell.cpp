#include "Cell.hpp"

#include "singleton/ResourceManager.hpp"

#include <string>

Cell::Cell() :
    rectangle{}, is_selected{}, is_correct{}, is_given{}, number{ 0 }
{

}

Cell::~Cell()
{

}

void Cell::SetRectangle(Rectangle new_rectangle)
{
    rectangle = new_rectangle;
}

void Cell::SetNumber(int new_number, bool given)
{
    number = new_number;
    is_given = given;
}

void Cell::ValidateNumber(int correct_number)
{
    is_correct = number == correct_number;
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
        DrawRectangleLinesEx(rectangle, 1.f, DARKGRAY);
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
        if (!is_given)
        {
            textColor = BLUE;
            if (!is_correct)
            {
                textColor = RED;
            }
        }

        DrawTextEx(font, std::to_string(number).c_str(), textPos, font_size,
            text_spacing, textColor);
    }
}

bool Cell::IsHovering() const
{
    return CheckCollisionPointRec(GetMousePosition(), rectangle);
}

bool Cell::IsCorrect() const
{
    return is_correct;
}

void Cell::SetSelect(bool select)
{
    is_selected = select;
}

bool Cell::IsSelected() const
{
    return is_selected;
}
