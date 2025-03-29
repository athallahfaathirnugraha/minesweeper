#ifndef _MINESWEEPER_H_
#define _MINESWEEPER_H_

#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    bool bomb;
    bool flagged;
} cell_t;

typedef struct
{
    cell_t *cells;
    size_t columns; // x size
    size_t rows; // y size
} minesweeper_t;

minesweeper_t new_minesweeper(size_t columns, size_t rows);
void destroy_minesweeper(minesweeper_t minesweeper);

#endif
