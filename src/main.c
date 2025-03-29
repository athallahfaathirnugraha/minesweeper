#include <stdio.h>
#include <stdlib.h>

#include <raylib.h>

#include "minesweeper.h"

int main()
{
    minesweeper_t game;
    
    InitWindow(600, 600, "minesweeper");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
