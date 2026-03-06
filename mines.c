#include "mines.h"

int number_of_mines(int rows, int columns, char *difficulty)
{
        int number_mines;
        int number_of_boxes = rows * columns;

        if (!strcmp(difficulty, EASY)) {
                number_mines = (int)ceil(number_of_boxes * PERCENTAGE_EASY); /*aufrunden, da mind. 1 Mine auf dem Feld sein soll, double Wert von ceil wird zu int Wert, da cast auf int*/
                return number_mines;
        }

        if (!strcmp(difficulty, INTERMEDIATE)) {
                number_mines = (int)ceil(number_of_boxes * PERCENTAGE_INTERMEDIATE);
                return number_mines;
        }

        if (!strcmp(difficulty, HARD)) {
                number_mines = (int)ceil(number_of_boxes * PERCENTAGE_HARD);
                return number_mines;
        }

        return FAILURE; /*wenn aufgrund eines Fehlers keine der if Bedingungen erreicht wurde*/
}

void generate_mines(int rows, int columns, int **mines, char *difficulty, int first_coordinates[])
{
        int i = 0, x, y;
        int number_mines = number_of_mines(rows, columns, difficulty);

        do {
                y = rand() % rows;
                x = rand() % columns;

                if(y == (first_coordinates[Y] - 1) && x == (first_coordinates[X] - 1)) { /*Das erste ausgewaehlte Feld darf keine Mine enthalten (-1, da der Array bei 0 zu zaehlen beginnt, die Koordinaten aber bei 1)*/
                        continue;
                }

                if(!mines[y][x]) { /*nur wenn dort nicht bereits eine Mine ist*/
                        mines[y][x] = MINE;
                        i++;
                }
        } while (i < number_mines);
}

int number_of_adjacent_mines(int rows, int columns, int coordinates[], int **mines)
{
        int i, j, number = 0, x, y;

        for (i = -2; i < 1; i++) { /*Y-Koordinate im Array ist Y - 1, Feld darueber: Y - 2, Feld darunter: Y*/

                for (j = -2; j < 1; j++) { /*X-Koordinate im Array ist X - 1, Feld links: X - 2, Feld rechts: X*/

                        y = coordinates[Y] + i;
                        x = coordinates[X] + j;

                        if (y >= 0 && y < rows && x >= 0 && x < columns) { /*x und y duerfen nicht ausserhalb des Spielfeldes liegen*/
                                if (mines[y][x] == MINE) {
                                        number++;
                                }
                        }
                }
        }
        return number;
}

void insert_mine_locations(int rows, int columns, int **field, int **mines)
{
        int i, j;
        for (i = 0; i < rows; i++) {
                for (j = 0; j < columns; j++) {
                        if (mines[i][j] == MINE) {
                                field[i][j] = MINE;
                        }
                }
        }
}
