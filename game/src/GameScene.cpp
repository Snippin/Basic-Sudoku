#include "GameScene.hpp"
#include "singleton/ResourceManager.hpp"

#include "raylib.h"

namespace
{
    ResourceManager *resource_manager = ResourceManager::Get();
}

GameScene::GameScene() :
    timer{ 0 }, selected_x{ -1 }, selected_y{ -1 }
{

}

GameScene::~GameScene()
{

}

void GameScene::Enter()
{
    Vector2 boardTileSize = { 50, 50 };
    Vector2 tileOffset = { 4, 4 };
    Vector2 screenHalf = {
        GetScreenWidth() * 0.5f - boardTileSize.x * 0.5f,
        GetScreenHeight() * 0.5f - boardTileSize.y * 0.5f
    };

    for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 9; x++)
        {
            float xpos = screenHalf.x +
                ((x - tileOffset.x) * boardTileSize.x);
            float ypos = screenHalf.y +
                ((y - tileOffset.y) * boardTileSize.y);

            cells[y][x].
                SetRectangle({ xpos, ypos, boardTileSize.x, boardTileSize.y });
        }
    }
}

void GameScene::Update()
{
    timer += GetFrameTime();
}

void GameScene::Render()
{
    int screen_width = GetScreenWidth();
    int screen_height = GetScreenHeight();
    Font font = resource_manager->GetFont();
    float font_size = font.baseSize * 3.f;
    float text_spacing = 4.f;

    // timer
    const char *text =
        TextFormat("%02d:%02d", (int)timer / 60, (int)timer % 60);
    Vector2 text_size = MeasureTextEx(font, text, font_size, text_spacing);
    Vector2 textPos =
    { screen_width * 0.5f - (text_size.x * 0.5f), font_size * 0.5f };
    DrawTextEx(font, text, textPos, font_size, text_spacing, WHITE);

    // render board
    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            Cell *cell = &cells[y][x];

            if (cell->IsHovering() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                SelectCell(x, y);
            }

            if (!cell->IsSelected())
            {
                cell->Render();
            }
        }
    }

    cells[selected_y][selected_x].Render();
}

void GameScene::Exit()
{

}

void GameScene::SelectCell(int x, int y)
{
    if (selected_x >= 0)
    {
        cells[selected_y][selected_x].SetSelect(false);
    }

    cells[y][x].SetSelect(true);

    selected_x = x;
    selected_y = y;
}
