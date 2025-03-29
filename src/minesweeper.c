#include "minesweeper.h"
#include "types.h"

#include <stdlib.h>
#include <stdbool.h>

#define BEGIN_RUN_FOR_ADJACENT_CELLS(x, y, columns, rows) \
    for (int _cx = (x) - 1; _cx <= (x) + 1; _cx++) { \
    for (int _cy = (y) - 1; _cy <= (y) + 1; _cy++) { \
        if ((_cx == (x) && _cy == (y)) || _cx < 0 || _cy < 0 || _cx >= (columns) || _cy >= (rows)) continue;

#define END_RUN_FOR_ADJACENT_CELLS }}

minesweeper_t new_minesweeper(size_t columns, size_t rows)
{
    minesweeper_t minesweeper;

    minesweeper.columns = columns;
    minesweeper.rows = rows;
    minesweeper.cells = calloc(sizeof(cell_t), columns * rows);

    generate_mines(minesweeper, 40, 50);
    calculate_bomb_num(minesweeper);

    return minesweeper;
}

void destroy_minesweeper(minesweeper_t minesweeper)
{
    free(minesweeper.cells);
}

cell_t *get_cell(minesweeper_t minesweeper, uchar x, uchar y)
{
    return &(minesweeper.cells[y * minesweeper.columns + x]);
}

void generate_mines(minesweeper_t minesweeper, uchar min, uchar max)
{
    int mine_num = min + rand() % (max - min + 1);
    
    for (int i = 0; i < mine_num; i++) {
        int cell_id;

        do { cell_id = rand() % (minesweeper.columns * minesweeper.rows); }
        while (minesweeper.cells[cell_id].bomb);

        minesweeper.cells[cell_id].bomb = true;
    }
}

uchar cell_bomb_num(minesweeper_t minesweeper, uchar x, uchar y)
{
    uchar count = 0;
    
    BEGIN_RUN_FOR_ADJACENT_CELLS(x, y, minesweeper.columns, minesweeper.rows)
        if (get_cell(minesweeper, _cx, _cy)->bomb) count++;
    END_RUN_FOR_ADJACENT_CELLS

    return count;
}

void calculate_bomb_num(minesweeper_t minesweeper)
{
    for (uchar x = 0; x < minesweeper.columns; x++) {
        for (uchar y = 0; y < minesweeper.rows; y++) {
            get_cell(minesweeper, x, y)->bomb_num = cell_bomb_num(minesweeper, x, y);
        }
    }
}

void open_cell(minesweeper_t minesweeper, uchar x, uchar y)
{
    cell_t *cell = get_cell(minesweeper, x, y);
    cell->opened = true;

    if (!cell->bomb && cell->bomb_num == 0) {
        BEGIN_RUN_FOR_ADJACENT_CELLS(x, y, minesweeper.columns, minesweeper.rows)
            if (!get_cell(minesweeper, _cx, _cy)->opened) {
                open_cell(minesweeper, _cx, _cy);
            }
        END_RUN_FOR_ADJACENT_CELLS
    }
}
