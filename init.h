#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

#include <stdlib.h>

#include "const.h"

int **field_init(int rows, int columns);
int **field_init_zeroes(int rows, int columns);
void free_field(int **field, int rows);
void fill_matrix_none_uncovered(int rows, int columns, int **matrix);

#endif
