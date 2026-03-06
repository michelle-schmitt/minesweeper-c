#ifndef GAME_LOOP_H_INLUDED
#define GAME_LOOP_H_INLUDED

#include <stdio.h>
#include <string.h>

#include "const.h"

int recursive_uncover(int rows, int columns, int coordinates[], int **mines, int **field);
int validate_uncover(int coordinates[], int **field);
int set_flag(int coordinates[],int **field);
int remove_flag(int coordinates[], int **field);
int minesweeper_game(int rows, int columns, int **field, int **mines, char *command, char *difficulty, int *number_of_commands);

#endif
