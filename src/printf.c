#include "printf.h"
#include "readandinput.h"

void print_grid(int rows, int columns, int **field)
{
        int i, j, row_number = 0; 
        int lines = 2 * rows + 1;

        system(CLEAR);

        for (i = -1; i < lines; i++) {

                if (i == -1) {
                        printf("  ");
                        for (j = 0; j < columns; j++) {
                                if ((j + 1) < 10) {
                                        printf("  %i ", (j + 1));  /*Spaltennamen ausgeben*/
                                } else {
                                        printf(" %i ", (j + 1));  /*Spaltennamen ausgeben*/
                                }
                        }
                        
                } else if ((i % 2) == 0) {

                        printf("  +");
                        for (j = 0; j < columns; j++) {
                                if ((i == 0 || i == (lines - 1)) && j != (columns - 1)) {
                                        printf("----");
                                } else {
                                        printf("---+");
                                }
                        }

                } else {

                        printf("%c |", (row_number + 'A'));  /*Zeilennamen ausgeben*/

                        for (j = 0; j < columns; j++) {
                                printf(" "); 
                                switch (field[row_number][j]) { /*Zahlen fuer Anzahl der Benachbarten Minen + Symbol fuer eine Mine ausgeben */
                                        case 0:
                                                printf("%i", field[row_number][j]);
                                                break;
                                        case 1:
                                                GREEN();
                                                printf("%i", field[row_number][j]);
                                                DEFAULT();
                                                break;
                                        case 2:
                                                CYAN();
                                                printf("%i", field[row_number][j]);
                                                DEFAULT();
                                                break;
                                        case 3:
                                                YELLOW();
                                                printf("%i", field[row_number][j]);
                                                DEFAULT();
                                                break;
                                        case 4:
                                        case 5:
                                        case 6:
                                        case 7:
                                        case 8: 
                                                PURPLE();
                                                printf("%i", field[row_number][j]);
                                                DEFAULT();
                                                break;
                                        case FLAG:
                                                RED();
                                                printf("F");
                                                DEFAULT();
                                                break;
                                        case MINE:
                                                RED();
                                                printf("*");
                                                DEFAULT();
                                                break;
                                        default:
                                                printf(" ");
                                                break;
                                }
                                printf(" |");
                        }
                        ++row_number;
                }

                printf("\n");
        }
        printf("\n");
}

void minesweeper_instructions(void)
{
        /*Quelle Schriftzug: https://github.com/cbonesteel/c-minesweeper#flag*/
        printf("    __  ____           _____                                  \n");
        printf("   /  |/  (_)___  ___ / ___/      _____  ___  ____  ___  _____\n");
        printf("  / /|_/ / / __ \\/ _ \\\\__ \\ | /| / / _ \\/ _ \\/ __ \\/ _ \\/ ___/\n");
        printf(" / /  / / / / / /  __/__/ / |/ |/ /  __/  __/ /_/ /  __/ /    \n");
        printf("/_/  /_/_/_/ /_/\\___/____/|__/|__/\\___/\\___/ .___/\\___/_/     \n");
        printf("                                          /_/\n");
        printf("\n");
        printf("Herzlich willkommen zum Spiel Minesweeper!\n");
        printf("Ziel des Spiels ist es, alle Felder aufzudecken, ohne auf eine Mine zu stossen.\n");
        printf("Das Spielfeld besteht aus Quadraten, die entweder leer sind oder eine Mine enthalten.\n");
        printf("Durch Zahlen auf den Feldern wird die Anzahl der Minen in den angrenzenden Feldern angezeigt.\n");
        printf("Es ist moeglich eine Markierung in Form einer Flagge auf einem Feld zu platzieren, wenn vermutet wird, dass sich dort eine Mine befindet.\n");
        printf("Wird eine Mine aufgedeckt, ist das Spiel verloren.\n");
        printf("Viel Spass!\n");
}

int help(void)
{
        printf("\nListe an moeglichen Befehlen:\n");
        printf("'%s' oder '%s': das naechste Feld soll aufgedeckt werden.\n", UNCOVER_FULL, UNCOVER_ABBR);
        printf("'%s' oder '%s': das naechste Feld soll mit einer Flagge (F) markiert werden.\n", FLAG_FULL, FLAG_ABBR);
        printf("'%s' oder '%s': die Markierung mit einer Flagge soll vom naechsten Feld entfernt werden.\n\n", REMOVE_FULL, REMOVE_ABBR);
        printf("\nBitte druecken Sie die Enter-Taste um fortzufahren.\n");

        if (read_input() == BUFFER_ERROR) { /*warten bis irgendeine Eingabe gemacht wurde*/
                return BUFFER_ERROR;
        }

        return VALID_INPUT;
}

void boom(void)
{
        printf("GAME OVER\n");
        printf("Das Spiel ist vorbei, Sie haben eine Mine (als * gekennzeichnet) getroffen und verloren!");
}

void win(void)
{
        printf("YOU WON\n");
        printf("Sie haben das Spiel erfolgreich beendet und alle Felder ohne Minen gefunden!");
}
