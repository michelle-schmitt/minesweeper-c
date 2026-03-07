#ifndef MINES_H_INCLUDED
#define MINES_H_INCLUDED

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "const.h"

int number_of_mines(int rows, int columns, char *difficulty);
void generate_mines(int rows, int columns, int **mines, char *difficulty, int first_coordinates[]);
int number_of_adjacent_mines(int rows, int columns, int coordinates[], int **mines);
void insert_mine_locations(int rows, int columns, int **field, int **mines);

#endif
