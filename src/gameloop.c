#include "gameloop.h"
#include "printf.h"
#include "mines.h"
#include "readandinput.h"
#include "init.h"

int recursive_uncover(int rows, int columns, int coordinates[], int **mines, int **field)
{
        int i, j, uncover = 0; /*Falls ein Feld mit einer 0 aufgedeckt wurde sollen alle umliegenden Felder aufgedeckt werden*/
        int coordinates_a[2];
        for (i = -1; i <= 1; i++) {

                for (j = -1; j <= 1; j++) {

                        coordinates_a[Y] = coordinates[Y] + i;
                        coordinates_a[X] = coordinates[X] + j;

                        if (((coordinates_a[Y]) > 0) && ((coordinates_a[Y]) <= rows)) { /*Beachten dass nicht über die Spalten hinaus gelesen wird*/

                                if (((coordinates_a[X]) > 0) && ((coordinates_a[X]) <= columns)) { /*Beachten dass nicht über die Reihen hinaus gelesen wird*/

                                        if (NOT_UNCOVERED == field[coordinates_a[Y] - 1][coordinates_a[X] - 1]) {

                                                if (0 == (field[coordinates_a[Y] - 1][coordinates_a[X] - 1] = number_of_adjacent_mines(rows, columns, coordinates_a, mines))) {
                                                        
                                                        uncover += recursive_uncover(rows, columns, coordinates_a, mines, field);
                                                }
                                                ++uncover;
                                        }
                                }
                        }
                }
        }
        return uncover;
}

int validate_uncover(int coordinates[], int **field)
{
        if (field[coordinates[Y] - 1][coordinates[X] - 1] == FLAG) { /*wenn ein Feld mit Flagge gewaehlt wird*/
                printf("Mit Flaggen markierte Felder koennen nicht aufgedeckt werden! Bitte geben Sie neue Koordinaten ein!\n");
                return FAILURE;
        }

        if (field[coordinates[Y] - 1][coordinates[X] - 1] != NOT_UNCOVERED) { /*wenn ein schon aufgedecktes Feld gewaehlt wird*/
                printf("Bereits aufgedeckte Felder koennen nicht nocheinmal aufgedeckt werden! Bitte geben Sie neue Koordinaten ein!\n");
                return FAILURE;
        }

        return SUCCESS;
}

int set_flag(int coordinates[],int **field)
{
        if (field[coordinates[Y] - 1][coordinates[X] - 1] == FLAG) { /*wenn schon eine Flagge auf dem Feld existiert*/
                printf("Das ausgewaehlte Feld hat bereits eine Flagge! Bitte geben Sie neue Koordinaten ein!\n");
                return FAILURE;
        }

        if (field[coordinates[Y] - 1][coordinates[X] - 1] != NOT_UNCOVERED) { /*wenn ein schon aufgedecktes Feld gewaehlt wird*/
                printf("Bereits aufgedeckte Felder koennen nicht mit einer Flagge markiert werden! Bitte geben Sie neue Koordinaten ein!\n");
                return FAILURE;
        }

        field[coordinates[Y] - 1][coordinates[X] - 1] = FLAG; /*Flagge setzen*/
        return SUCCESS;
}

int remove_flag(int coordinates[], int **field)
{
        if (field[coordinates[Y] - 1][coordinates[X] - 1] == FLAG) { /*Test, ob Feld mit Flagge gewaehlt wurde*/                    
                field[coordinates[Y] - 1][coordinates[X] - 1] = NOT_UNCOVERED; /*Flagge entfernen*/
                return SUCCESS;
        }
        
        /*wenn ein Feld ohne Flagge gewaehlt wurde*/
        printf("Auf dem ausgewaehlten Feld existiert keine Flagge! Bitte geben Sie neue Koordinaten ein!\n");
        return FAILURE;
}

int minesweeper_game(int rows, int columns, int **field, int **mines, char *command, char *difficulty, int *number_of_commands)
{

        int uncovered_boxes = 0;
        int status, uncover_to_win;
        int coordinates[DIMENSIONS];

        fill_matrix_none_uncovered(rows, columns, field); /*Das Spielfeld mit keinem aufgedeckten Feld erstellen*/

        uncover_to_win = (rows * columns) - number_of_mines(rows, columns, difficulty);

        print_grid(rows, columns, field);

        while (1) { /*falls status == ESC: nochmal fragen*/

                status = read_coordinates(rows, columns, coordinates); /*das erste Feld aufdecken*/
                if (status == BUFFER_ERROR) {
                        return BUFFER_ERROR;
                }

                if (status == VALID_INPUT) {
                        break;
                }
        }

        ++uncovered_boxes; /*das erste Feld wurde aufgedeckt (darf keine Mine enthalten)*/
        ++(*number_of_commands); /*das erste Feld wurde aufgedeckt = uncover, auch wenn noch nicht gefragt (einzige Moeglichkeit)*/

        generate_mines(rows, columns, mines, difficulty, coordinates); /*nachdem das erste Feld aufgedeckt wurde, werden die Minen generiert*/


        /*Die Nummer an anliegeneden Minen des ersten ausgewaehlten Feldes berechnen:*/
        if (0 == (field[coordinates[Y] - 1][coordinates[X] - 1] = number_of_adjacent_mines(rows, columns, coordinates, mines))) {
                uncovered_boxes += recursive_uncover(rows, columns, coordinates, mines, field);
        } /*Koordinate - 1, da die Koordinaten bei 1 beginnen, der Array aber bei 0*/

        while (1) { /*Befehl auslesen*/

                print_grid(rows, columns, field);

                status = read_command(command);
                if (status == BUFFER_ERROR) {
                        return BUFFER_ERROR;
                }

                if (!strcmp(command, HELP)) { /*wenn help eingegeben wurde (zaehlt nicht zu der Anzahl an Befehlen)*/
                        if (help() == BUFFER_ERROR) {
                                return BUFFER_ERROR;
                        }
                        continue;
                }

                while (1) { /*Koordinaten auslesen*/

                        status = read_coordinates(rows, columns, coordinates);
                        if (status == BUFFER_ERROR) {
                                return BUFFER_ERROR;
                        }

                        if (status == ESC) { /*wenn der Benutzer zurueck zur Befehlseingabe springen moechte*/
                                break; /*zurueck zur Eingabe eines Befehls*/
                        }

                        if (!strcmp(command, UNCOVER_FULL) || !strcmp(command, UNCOVER_ABBR)) { /*wenn als Befehl uncover oder u eingegeben wurde*/

                                if (validate_uncover(coordinates, field) == FAILURE) {
                                        continue;
                                }

                                ++(*number_of_commands); /*ungueltige Eingaben werden nicht mitgezaehlt (zur besseren Vergleichbarkeit zwischen Spielen/Benutzern)*/

                                if (mines[coordinates[Y] - 1][coordinates[X] - 1] == MINE) { /*wenn auf dem ausgewaehlten Feld eine Mine liegt*/
                                        
                                        insert_mine_locations(rows, columns, field, mines);
                                        print_grid(rows, columns, field);

                                        return LOST;
                                }
                                
                                if (0 == (field[coordinates[Y] - 1][coordinates[X] - 1] = number_of_adjacent_mines(rows, columns, coordinates, mines))) {
                                        uncovered_boxes += recursive_uncover(rows, columns, coordinates, mines, field);
                                }

                                uncovered_boxes++;
                                
                                if (uncovered_boxes == uncover_to_win) { /*wenn alle Felder aufgedeckt wurde, die keine Mine enthalten*/
                                        insert_mine_locations(rows, columns, field, mines);
                                        print_grid(rows, columns, field);

                                        return WIN;
                                }

                                break; /*zurueck zur Eingabe eines Befehls*/

                        }

                        if (!strcmp(command, FLAG_FULL) || !strcmp(command, FLAG_ABBR)) {

                                if (set_flag(coordinates, field) == FAILURE) { /*wenn ungueltige Koordinaten eingegeben wurden*/
                                        continue; /*neue Abfrage von Koordinaten*/
                                }

                                ++(*number_of_commands);

                                break; /*zurueck zur Eingabe eines Befehls*/
                        }

                        if (!strcmp(command, REMOVE_FULL) || !strcmp(command, REMOVE_ABBR)) {

                                if (remove_flag(coordinates, field) == FAILURE) {
                                        continue; /*neue Abfrage von Koordinaten*/
                                }
                                ++(*number_of_commands);

                                break; /*zurueck zur Eingabe eines Befehls*/
                        }
                }
        }
}
