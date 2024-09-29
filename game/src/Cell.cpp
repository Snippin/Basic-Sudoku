#include "Cell.hpp"


Cell::Cell() : rectangle{}, is_selected{}
{

}

Cell::~Cell()
{

}

void Cell::SetRectangle(Rectangle new_rectangle)
{
    rectangle = new_rectangle;
}

void Cell::Render()
{
    if (is_selected)
    {
        DrawRectangleLinesEx(rectangle, 1.5f, YELLOW);
    }
    else
    {
        DrawRectangleLinesEx(rectangle, 1, DARKGRAY);
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
