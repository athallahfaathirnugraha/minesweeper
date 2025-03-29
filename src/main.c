#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#include <raylib.h>

#include "minesweeper.h"

typedef enum
{
    scr_game,
    scr_over,
    scr_win,
} screen_t;

void draw_cell(
    minesweeper_t game,
    int x,
    int y,
    screen_t screen,
    Texture2D flag_texture,
    Texture2D bomb_texture
) {
    static uint cell_size = 38;

    int cell_id = y * 16 + x;
    cell_t cell = game.cells[cell_id];

    DrawRectangle(x * cell_size, y * cell_size, cell_size, cell_size, LIGHTGRAY);
    DrawRectangleLines(x * cell_size, y * cell_size, cell_size, cell_size, DARKGRAY);

    Rectangle src_rect = { .x = 0, .y = 0, .width = 512, .height = 512 };

    Rectangle dst_rect = {
        .x = x * cell_size,
        .y = y * cell_size,
        .width = cell_size,
        .height = cell_size
    };

    if (cell.flagged && !cell.opened) {
        DrawTexturePro(
            flag_texture,
            src_rect,
            dst_rect,
            (Vector2){ .x = 0, .y = 0 },
            0.f,
            WHITE
        );
    }

    if (screen == scr_game && !cell.opened) return;

    DrawRectangle(x * cell_size, y * cell_size, cell_size, cell_size, DARKGRAY);

    if (cell.bomb) {
        DrawTexturePro(
            bomb_texture,
            src_rect,
            dst_rect,
            (Vector2){ .x = 0, .y = 0 },
            0.f,
            WHITE
        );
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

void game_screen_update(screen_t *screen, minesweeper_t *game)
{
    int x = GetMouseX() / 38;
    int y = GetMouseY() / 38;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        open_cell(*game, x, y);
        if (get_cell(*game, x, y)->bomb) *screen = scr_over;

        if (won(*game)) {
            *screen = scr_win;
            return;
        }
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) || IsKeyPressed(KEY_F)) {
        get_cell(*game, x, y)->flagged = !get_cell(*game, x, y)->flagged;
    }
}

void over_screen_update(screen_t *screen, minesweeper_t *game)
{
    if (IsKeyPressed(KEY_R)) {
        destroy_minesweeper(*game);
        *game = new_minesweeper(16, 16);

        *screen = scr_game;
    }
}

void win_screen_update(screen_t *screen, minesweeper_t *game)
{
    if (IsKeyPressed(KEY_R)) {
        destroy_minesweeper(*game);
        *game = new_minesweeper(16, 16);

        *screen = scr_game;
    }
}

int main(void)
{
    srand(time(NULL));
    screen_t screen = scr_game;
    
    minesweeper_t game = new_minesweeper(16, 16);

    double elapsed = 0.f;
    
    InitWindow(608, 608, "minesweeper");
    SetTargetFPS(60);

    Texture2D flag_texture = LoadTexture("resources/flag.png");
    Texture2D bomb_texture = LoadTexture("resources/bomb.png");

    while (!WindowShouldClose()) {
        double dt = GetFrameTime();
        elapsed += dt;

        switch (screen) {
            case scr_game:
                game_screen_update(&screen, &game);
                break;
            case scr_over:
                over_screen_update(&screen, &game);
                break;
            case scr_win:
                win_screen_update(&screen, &game);
                break;
        }
        
        BeginDrawing();
        ClearBackground(BLACK);

        for (int x = 0; x < 16; x++) {
            for (int y = 0; y < 16; y++) {
                draw_cell(game, x, y, screen, flag_texture, bomb_texture);
            }
        }
        
        if (screen == scr_over || screen == scr_win) {
            char *text =
                screen == scr_over
                ? "you lose\n\n\n\nR to restart"
                : "you win!\n\n\n\nR to restart";

            float font_size = 60 + 4 * sin(elapsed);
            float spacing = 4;
            Vector2 text_size = MeasureTextEx(GetFontDefault(), text, font_size, spacing);

            Vector2 text_pos = {
                .x = 304 - text_size.x / 2.f,
                .y = 304 - text_size.y / 2.f
            };

            DrawTextEx(GetFontDefault(), text, text_pos, font_size, spacing, GREEN);
        }
        
        EndDrawing();
    }

    UnloadTexture(flag_texture);
    UnloadTexture(bomb_texture);

    CloseWindow();

    destroy_minesweeper(game);

    return 0;
}
