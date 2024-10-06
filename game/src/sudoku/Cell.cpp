#include "Cell.hpp"

#include "core/ResourceManager.hpp"
#include "raylib.h"

#include <string>

Cell::Cell() :
    rectangle{}, is_selected{}, is_correct{}, is_given{}, is_highlighted{},
    number{ 0 }, notes{}
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

    // render border
    if (is_selected)
    {
        DrawRectangleLinesEx(rectangle, 1.5f, YELLOW);
    }
    else
    {
        DrawRectangleLinesEx(rectangle, 1.f, DARKGRAY);
    }

    // render background
    if (is_highlighted)
    {
        Color highlightColor = SKYBLUE;
        highlightColor.a -= 155;
        DrawRectangleRec(rectangle, highlightColor);
    }

    // render notes
    if (number == 0)
    {
        float note_size = font_size * 0.333f;
        float note_spacing = text_spacing * 0.333f;
        Vector2 text_position = { rectangle.x + note_size * 0.3f, rectangle.y };

        std::string notes_str = "";
        for (int i = 0; i < 9; i++)
        {
            int row = i / 3;
            int col = i % 3;
            Vector2 position = { text_position.x + (col * note_size),
                text_position.y + (row * note_size) };

            if (notes[i])
            {
                notes_str += TextFormat("%d", i + 1);
                DrawTextEx(font, std::to_string(i + 1).c_str(), position,
                    note_size, note_spacing, LIGHTGRAY);
            }
        }
    }
    // render number
    else
    {
        Vector2 text_size = MeasureTextEx(font, std::to_string(number).c_str(),
            font_size, text_spacing);
        Vector2 text_position = {
            rectangle.x + rectangle.width * 0.5f - text_size.x * 0.5f,
            rectangle.y + rectangle.height * 0.05f
        };

        Color text_color = WHITE;
        if (!is_given)
        {
            text_color = BLUE;
            if (!is_correct)
            {
                text_color = RED;
            }
        }

        DrawTextEx(font, std::to_string(number).c_str(), text_position,
            font_size, text_spacing, text_color);
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

void Cell::SetHighlight(bool highlight)
{
    is_highlighted = highlight;
}

void Cell::SetNote(int number)
{
    notes[number - 1] = !notes[number - 1];
}
