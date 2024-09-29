#include "Cell.hpp"


void Cell::SetRectangle(Rectangle new_rectangle)
{
    rectangle = new_rectangle;
}

void Cell::Render()
{
    DrawRectangleLinesEx(rectangle, 1, DARKGRAY);
}
