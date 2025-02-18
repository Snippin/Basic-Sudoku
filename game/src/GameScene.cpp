#include "GameScene.hpp"

#include "raylib.h"
#include "core/raygui.h"
#include "core/ResourceManager.hpp"
#include "sudoku/DifficultyLevel.hpp"

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>

#pragma region Static Functions
#if _DEBUG
static void PrintGridInConsole(int grid[9][9])
{

    for (int row = 0; row < 9; row++)
    {
        std::for_each(std::begin(grid[row]), std::end(grid[row]), [](int num)
        {
            if (num == 0)
            {
                printf(".");
            }
            else
            {
                printf("%d", num);
            }

            printf("|");
        });

        printf("\n");
    }
}
#endif
#pragma endregion


GameScene::GameScene() :
    difficulty_level{ DifficultyLevel::MEDIUM }, display_grid{},
    solution_grid{}, cells{}, regions{}, selected_x{ -1 }, selected_y{ -1 },
    note_placing_mode{}, remaining_space{ 0 }, game_over{}, timer{ 0 },
    wrong_inputs{ 0 }
{

}

void GameScene::Enter()
{
    srand(static_cast<unsigned>(time(nullptr)));
    InitialiseGridPositions();
    StartGame();
}

void GameScene::Update()
{
    if (!game_over)
    {
        timer += GetFrameTime();
    }

    // handle inputs
    {
        if (IsKeyPressed((KEY_L)))
        {
            EndGame();
        }

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
    Vector2 screen_half = { static_cast<float>(screen_width) * 0.5f,
        static_cast<float>(GetScreenHeight()) * 0.5f };
    Font font = ResourceManager::Get()->GetFont();
    float font_size = static_cast<float>(font.baseSize)* 3.f;
    float text_spacing = 4.f;

    // timer
    const char *text =
        TextFormat("%02d:%02d", static_cast<int>(timer) / 60,
            static_cast<int>(timer) % 60);
    Vector2 text_size = MeasureTextEx(font, text, font_size, text_spacing);
    Vector2 text_pos = {
        static_cast<float>(screen_width) * 0.5f - (text_size.x * 0.5f),
        font_size * 0.5f };
    DrawTextEx(font, text, text_pos, font_size, text_spacing, WHITE);

    // wrong inputs
    text = TextFormat("Errors: %d", wrong_inputs);
    text_size = MeasureTextEx(font, text, font_size, text_spacing);
    text_pos = { static_cast<float>(screen_width) - (text_size.x * 1.5f),
    screen_half.y - (font_size * 0.5f) };
    DrawTextEx(font, text, text_pos, font_size, text_spacing, RED);

    RenderGrid();
    if (game_over)
    {
        RenderEnd();
    }
}

void GameScene::RenderGrid()
{
    // render cells
    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            Cell *cell = &cells[y][x];

            if (cell->IsHovering() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
                !game_over)
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
    for (const auto region : regions)
    {
        DrawRectangleLinesEx(region, 2.5f, GRAY);
    }

    if (selected_x >= 0)
    {
        cells[selected_y][selected_x].Render();
    }
}

void GameScene::RenderEnd()
{
    int screen_height = GetScreenHeight();
     Vector2 screen_half = { static_cast<float>(GetScreenWidth()) * 0.5f,
         static_cast<float>(screen_height) * 0.5f };

    // buttons
    Vector2 button_size = { 200, 50 };
    Vector2 button_position = {
        screen_half.x - (button_size.x * 0.5f),
        static_cast<float>(screen_height) - (button_size.y * 1.5f) };

    if (GuiButton({ button_position.x, button_position.y, button_size.x,
        button_size.y }, "Replay"))
    {
        StartGame();
    }
}

void GameScene::InitialiseGridPositions()
{
    // initialise 9x9 cell positions
    Vector2 boardTileSize = { 50, 50 };
    Vector2 tileOffset = { 4, 4 };
    Vector2 screenHalf = {
        static_cast<float>(GetScreenWidth()) * 0.5f - boardTileSize.x * 0.5f,
        static_cast<float>(GetScreenHeight()) * 0.5f - boardTileSize.y * 0.5f
    };

    for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 9; x++)
        {
            float x_pos = screenHalf.x +
                ((static_cast<float>(x) - tileOffset.x) * boardTileSize.x);
            float y_pos = screenHalf.y +
                ((static_cast<float>(y) - tileOffset.y) * boardTileSize.y);

            cells[y][x].
                SetRectangle({ x_pos, y_pos, boardTileSize.x, boardTileSize.y });
        }
    }

    // initialise small 3x3 region positions
    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            float x_pos = screenHalf.x +
                ((static_cast<float>(x) - 1.3333f) * boardTileSize.x * 3);
            float y_pos = screenHalf.y +
                ((static_cast<float>(y) - 1.3333f) * boardTileSize.y * 3);

            regions[3 * y + x] = { x_pos , y_pos, boardTileSize.x * 3,
                boardTileSize.y * 3 };
        }
    }
}

void GameScene::StartGame()
{
    timer = 0;
    wrong_inputs = 0;
    note_placing_mode = false;
    game_over= false;

    generator.GeneratePuzzle(display_grid, solution_grid, difficulty_level);
    for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 9; x++)
        {
            cells[y][x].SetNumber(display_grid[y][x], true);
            cells[y][x].ValidateNumber(solution_grid[y][x]);

            if (display_grid[y][x] == 0)
            {
                remaining_space++;
            }
        }
    }

#if _DEBUG
    printf("\nGRID\n");
    PrintGridInConsole(display_grid);

    printf("\nSOLUTION\n");
    PrintGridInConsole(solution_grid);

    printf("empty spaces: %d\n", remaining_space);
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
        int initial_number = cells[selected_y][selected_x].GetNumber();

        cells[selected_y][selected_x].SetNumber(number);
        cells[selected_y][selected_x].
            ValidateNumber(solution_grid[selected_y][selected_x]);

        CheckBoard(initial_number, number);
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

void GameScene::CheckBoard(int initial_number, int input_number)
{
    if (cells[selected_y][selected_x].IsCorrect())
    {
        remaining_space--;
        if (remaining_space == 0)
        {
            EndGame();
        }
    }
    else if (input_number != initial_number && input_number != 0)
    {
        wrong_inputs++;
    }
}

void GameScene::EndGame()
{
    HighlightRowCol(false);
    cells[selected_y][selected_x].SetSelect(false);
    selected_x = -1;
    selected_y = -1;

    game_over = true;
}
