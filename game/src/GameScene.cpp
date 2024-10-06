#include "GameScene.hpp"

#include "raylib.h"
#include "singleton/ResourceManager.hpp"
#include "DifficultyLevel.hpp"

#include <cstdio>
#include <cstdlib>
#include <ctime>

GameScene::GameScene() :
    difficulty_level{ DifficultyLevel::MEDIUM }, timer{ 0 }, cells{}, regions{},
    selected_x{ -1 }, selected_y{ -1 }, note_placing_mode{}
{

}

GameScene::~GameScene()
{

}

void GameScene::Enter()
{
    srand(time(NULL));
    InitialiseGridPositions();
    StartGame();
}

void GameScene::Update()
{
    timer += GetFrameTime();

    // handle inputs
    {
        if (IsKeyPressed(KEY_N))
        {
            note_placing_mode = !note_placing_mode;
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            SetCellNumber(0);
        }
        else if (IsKeyPressed(KEY_ONE) || IsKeyPressed(KEY_KP_1))
        {
            SetCellNumber(1);
        }
        else  if (IsKeyPressed(KEY_TWO) || IsKeyPressed(KEY_KP_2))
        {
            SetCellNumber(2);
        }
        else  if (IsKeyPressed(KEY_THREE) || IsKeyPressed(KEY_KP_3))
        {
            SetCellNumber(3);
        }
        else  if (IsKeyPressed(KEY_FOUR) || IsKeyPressed(KEY_KP_4))
        {
            SetCellNumber(4);
        }
        else  if (IsKeyPressed(KEY_FIVE) || IsKeyPressed(KEY_KP_5))
        {
            SetCellNumber(5);
        }
        else  if (IsKeyPressed(KEY_SIX) || IsKeyPressed(KEY_KP_6))
        {
            SetCellNumber(6);
        }
        else  if (IsKeyPressed(KEY_SEVEN) || IsKeyPressed(KEY_KP_7))
        {
            SetCellNumber(7);
        }
        else  if (IsKeyPressed(KEY_EIGHT) || IsKeyPressed(KEY_KP_8))
        {
            SetCellNumber(8);
        }
        else  if (IsKeyPressed(KEY_NINE) || IsKeyPressed(KEY_KP_9))
        {
            SetCellNumber(9);
        }
    }
}

void GameScene::Render()
{
    int screen_width = GetScreenWidth();
    int screen_height = GetScreenHeight();
    Font font = ResourceManager::Get()->GetFont();
    float font_size = font.baseSize * 3.f;
    float text_spacing = 4.f;

    // timer
    const char *text =
        TextFormat("%02d:%02d", (int)timer / 60, (int)timer % 60);
    Vector2 text_size = MeasureTextEx(font, text, font_size, text_spacing);
    Vector2 textPos =
    { screen_width * 0.5f - (text_size.x * 0.5f), font_size * 0.5f };
    DrawTextEx(font, text, textPos, font_size, text_spacing, WHITE);

    // render cells
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

    // render 3x3 regions
    for (int i = 0; i < 9; i++)
    {
        DrawRectangleLinesEx(regions[i], 2.5f, GRAY);
    }

    if (selected_x >= 0)
    {
        cells[selected_y][selected_x].Render();
    }
}

void GameScene::Exit()
{

}

void GameScene::InitialiseGridPositions()
{
    // initialise 9x9 cell positions
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

    // initialise small 3x3 region positions
    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            float xpos = screenHalf.x +
                ((x - 1.3333) * boardTileSize.x * 3);
            float ypos = screenHalf.y +
                ((y - 1.3333) * boardTileSize.y * 3);

            regions[3 * y + x] = { xpos , ypos, boardTileSize.x * 3,
                boardTileSize.y * 3 };
        }
    }
}

void GameScene::StartGame()
{
    generator.GeneratePuzzle(display_grid, solution_grid, difficulty_level);

    for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 9; x++)
        {
            cells[y][x].SetNumber(display_grid[y][x], true);
            cells[y][x].ValidateNumber(solution_grid[y][x]);
        }
    }

#if _DEBUG
    printf("\nGRID\n");
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (display_grid[i][j] == 0)
            {
                printf(".");
            }
            else
            {
                printf("%d", display_grid[i][j]);
            }

            printf("|");
        }
        printf("\n");
    }

    printf("\SOLN\n");
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (solution_grid[i][j] == 0)
            {
                printf(".");
            }
            else
            {
                printf("%d", solution_grid[i][j]);
            }

            printf("|");
        }
        printf("\n");
    }
#endif
}

void GameScene::SelectCell(int x, int y)
{
    if (selected_x >= 0)
    {
        cells[selected_y][selected_x].SetSelect(false);
    }

    HighlightRowCol(false);

    selected_x = x;
    selected_y = y;
    cells[y][x].SetSelect(true);

    HighlightRowCol(true);
}

void GameScene::SetCellNumber(int number)
{
    if (selected_x < 0 || cells[selected_y][selected_x].IsCorrect())
    {
        return;
    }

    if (note_placing_mode)
    {
        cells[selected_y][selected_x].SetNote(number);
    }
    else
    {
        cells[selected_y][selected_x].SetNumber(number);
        cells[selected_y][selected_x].
            ValidateNumber(solution_grid[selected_y][selected_x]);
    }
}

void GameScene::HighlightRowCol(bool highlight)
{
    for (int i = 0; i < 9; i++)
    {
        cells[selected_y][i].SetHighlight(highlight);
        cells[i][selected_x].SetHighlight(highlight);
    }
}
