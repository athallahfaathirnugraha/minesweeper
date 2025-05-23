#ifndef _MINESWEEPER_H_
#define _MINESWEEPER_H_

#include <stdlib.h>
#include <stdbool.h>

#include "types.h"

typedef struct
{
    bool bomb;
    bool flagged;
    uchar bomb_num;
    bool opened;
} cell_t;

typedef struct
{
    cell_t *cells;
    size_t columns; // x size
    size_t rows; // y size
} minesweeper_t;

minesweeper_t new_minesweeper(size_t columns, size_t rows);
void destroy_minesweeper(minesweeper_t minesweeper);

cell_t *get_cell(minesweeper_t minesweeper, uchar x, uchar y);

bool won(minesweeper_t minesweeper);

// the given minesweeper must be emptied
// does not calculate bomb_num
void generate_mines(minesweeper_t minesweeper, uchar min, uchar max);

// calculate the bomb num for a cell
uchar cell_bomb_num(minesweeper_t minesweeper, uchar x, uchar y);

// calculates the bomb_num for each cell
void calculate_bomb_num(minesweeper_t minesweeper);

// open a cell. if blank will open adjacent cells
void open_cell(minesweeper_t, uchar x, uchar y);

#endif
