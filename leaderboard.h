#ifndef LEADERBOARD_H_INLUDED
#define LEADERBOARD_H_INLUDED

#include <stdio.h>
#include <string.h>

#include "const.h"

int read_leaderboard_entries(Entry leaderboard[], char *difficulty, int *number_of_entries);
void swap_entries(char *leaderboard_name, double *leaderboard_seconds, int *leaderboard_number_of_commands, char *name, double *seconds_since_start, int *number_of_commands);
int add_to_leaderboard(int number_of_commands, double seconds_since_start, char *difficulty, char name[]);
int print_leaderboard(char *difficulty);
int leaderboard(int number_of_commands, double seconds_since_start, char *difficulty, int result);

#endif
