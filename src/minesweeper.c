#include "minesweeper.h"
#include "types.h"

#include <stdlib.h>
#include <stdbool.h>

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

void calculate_bomb_num(minesweeper_t minesweeper)
{
    // TODO
}
