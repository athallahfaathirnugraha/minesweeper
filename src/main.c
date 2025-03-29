#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <raylib.h>

#include "minesweeper.h"

int main()
{
    minesweeper_t game = new_minesweeper(16, 16);
    
    InitWindow(600, 600, "minesweeper");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
    }

    CloseWindow();

    destroy_minesweeper(game);

    return 0;
}
