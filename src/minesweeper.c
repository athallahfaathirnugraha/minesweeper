#include "minesweeper.h"

#include <stdlib.h>

minesweeper_t new_minesweeper(size_t columns, size_t rows)
{
    minesweeper_t minesweeper;

    minesweeper.columns = columns;
    minesweeper.rows = rows;
    minesweeper.cells = malloc(sizeof(cell_t) * columns * rows);

    return minesweeper;
}

void destroy_minesweeper(minesweeper_t minesweeper)
{
    free(minesweeper.cells);
}
