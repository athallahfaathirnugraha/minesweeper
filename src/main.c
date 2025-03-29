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
        
        DrawText(text, x * cell_size, y * cell_size, 30, BLACK);
    }
}

int main()
{
    srand(time(NULL));
    
    minesweeper_t game = new_minesweeper(16, 16);
    
    InitWindow(608, 608, "minesweeper");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            int x = GetMouseX() / 38;
            int y = GetMouseY() / 38;

            get_cell(game, x, y)->opened = true;
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
