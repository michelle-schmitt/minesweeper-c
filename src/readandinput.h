#ifndef READANDINPUT_H_INCLUDED
#define READANDINPUT_H_INCLUDED

#include <stdio.h>
#include <string.h>

#include "const.h"

int flush_buff(void);
int read_name(char name[]);
int read_yes_or_no(char answer[]);
int read_command(char *command);
int read_difficulty(char *difficulty);
int read_coordinates(int rows, int columns, int coordinate[]);
int read_input(void);

#endif
