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

    if (game.cells[cell_id].bomb) {
        DrawText("bomb", x * cell_size, y * cell_size, 20, RED);
    }
}

int main()
{
    srand(time(NULL));
    
    minesweeper_t game = new_minesweeper(16, 16);
    
    InitWindow(608, 608, "minesweeper");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
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
