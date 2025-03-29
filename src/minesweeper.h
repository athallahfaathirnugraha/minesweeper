#ifndef _MINESWEEPER_H_
#define _MINESWEEPER_H_

#include <stdbool.h>

typedef struct
{
    bool bomb;
    bool flagged;
} cell_t;

typedef struct
{
    cell_t cells[100];
} minesweeper_t;

#endif
