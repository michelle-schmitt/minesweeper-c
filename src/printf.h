#ifndef PRINTF_H_INCLUDED
#define PRINTF_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "const.h"

#ifdef _WIN32
    #include <windows.h>
    #define CLEAR "cls"
#else
    #include <unistd.h>
    #define CLEAR "clear"
#endif

void print_grid(int rows, int columns, int **field);
void minesweeper_instructions(void);
int help(void);
void boom(void);
void win(void);

#endif
