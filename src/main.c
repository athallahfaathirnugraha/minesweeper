#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include <raylib.h>

#include "minesweeper.h"

int main()
{
    srand(time(NULL));
    
    minesweeper_t game = new_minesweeper(16, 16);
    
    InitWindow(608, 608, "minesweeper");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        int cell_size = 38;

        for (int x = 0; x < 16; x++) {
            for (int y = 0; y < 16; y++) {
                int cell_id = y * 16 + x;

                if (game.cells[cell_id].bomb) {
                    DrawText("bomb", x * cell_size, y * cell_size, 20, RED);
                }
            }
        }
        
        EndDrawing();
    }

    CloseWindow();

    destroy_minesweeper(game);

    return 0;
}
