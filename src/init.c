#include "init.h"

int **field_init(int rows, int columns)
{
        int i, j;
        int **field = malloc(rows * sizeof(int*));

        if (field == NULL) {
                return NULL;
        }

        for (i = 0; i < rows; i++) {

                field[i] = malloc(columns * sizeof(int));

                if (field[i] == NULL) {

                        for (j = 0; j < i; j++) {
                                free(field[j]);
                        }
                        free(field);
                        return NULL;
                }
        }
        return field;
}

int **field_init_zeroes(int rows, int columns)
{
        int i, j;
        int **field = malloc(rows * sizeof(int*));

        if (field == NULL) {
                return NULL;
        }

        for (i = 0; i < rows; i++) {

                field[i] = calloc(columns, sizeof(int)); /*Speicher freigeben und mit Nullen fuellen*/

                if (field[i] == NULL) {

                        for (j = 0; j < i; j++) {
                                free(field[j]);
                        }
                        free(field);
                        return NULL;
                }
        }
        return field;
}

void free_field(int **field, int rows)
{
        int i;
        for (i = 0; i < rows; i++) { /*Speicherplatz wieder freigeben*/
                free(field[i]);
        }
        free(field);
}

void fill_matrix_none_uncovered(int rows, int columns, int **matrix)
{
        int i, j;
        for (i = 0; i < rows; i++) {
                for (j = 0; j < columns; j++) {
                        matrix[i][j] = NOT_UNCOVERED;
                }
        }
}
