#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include <raylib.h>

#include "minesweeper.h"

void draw_cell(minesweeper_t game, int x, int y)
{
    static uint cell_size = 38;

    int cell_id = y * 16 + x;
    cell_t cell = game.cells[cell_id];

    DrawRectangle(x * cell_size, y * cell_size, cell_size, cell_size, LIGHTGRAY);
    DrawRectangleLines(x * cell_size, y * cell_size, cell_size, cell_size, DARKGRAY);

    if (!cell.opened) return;

    DrawRectangle(x * cell_size, y * cell_size, cell_size, cell_size, DARKGRAY);

    if (cell.bomb) {
        DrawText("bomb", x * cell_size, y * cell_size, 20, RED);
    } else if (cell.bomb_num > 0) {
        char text[2];
        sprintf(text, "%d", cell.bomb_num);
        
        int font_size = 25;
        Vector2 text_size = MeasureTextEx(GetFontDefault(), text, font_size, 0);

        Vector2 text_pos = {
            .x = x * cell_size + cell_size / 2.f - text_size.x / 2.f,
            .y = y * cell_size + cell_size / 2.f - text_size.y / 2.f
        };

        DrawTextEx(GetFontDefault(), text, text_pos, font_size, 0, BLACK);
    }
}

int main(void)
{
    srand(time(NULL));
    
    minesweeper_t game = new_minesweeper(16, 16);
    
    InitWindow(608, 608, "minesweeper");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            int x = GetMouseX() / 38;
            int y = GetMouseY() / 38;

            open_cell(game, x, y);
        }

        BeginDrawing();
        ClearBackground(BLACK);

        for (int x = 0; x < 16; x++) {
            for (int y = 0; y < 16; y++) {
                draw_cell(game, x, y);
            }
        }
        
        EndDrawing();
    }

    CloseWindow();

    destroy_minesweeper(game);

    return 0;
}
