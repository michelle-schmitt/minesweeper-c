#include "readandinput.h"

int flush_buff(void) 
{
        char c = '\0';
        while ((c = getchar ()) != '\n' && c != EOF);
        return c != EOF;
}

int read_name(char name[])
{
        char c = '\0';
        int status;

        while(1) {
                printf("\nBitte geben Sie Ihren Namen fuer die Bestenliste ein (max. %i Zeichen).\n", MAX_STRING_NAME);

                status = scanf("%"STRINGIFY_VAL(MAX_STRING_NAME)"s", name); /*maximale Eingabe: MAX_STRING_NAME-Zeichen*/

                if (status == EOF) { /*Test auf Pufferfehler, falls txt Datei eingelesen wird (nicht empfohlen)*/
                        return BUFFER_ERROR;
                }

                if (status == 0 || (c = getchar()) != '\n') {

                        if (c == EOF || !flush_buff()) {
                                return BUFFER_ERROR;
                        }

                        printf("Ungueltige Eingabe, bitte versuchen Sie es erneut!\n");
                        continue; /*Benutzer wird solange nach einer Eingabe gefragt, bis diese gueltig ist*/
                }

                return VALID_INPUT;
        }
}

int read_yes_or_no(char answer[])
{
        char c = '\0';
        int status;

        while(1) {

                printf("Bitte geben Sie '%s' oder '%s' ein.\n", YES, NO);

                status = scanf("%"STRINGIFY_VAL(MAX_STRING_YES_OR_NO)"s", answer);

                if (status == EOF) { /*Test auf Pufferfehler, falls txt Datei eingelesen wird (nicht empfohlen)*/
                        return BUFFER_ERROR;
                }

                if (status == 0 || (c = getchar()) != '\n') {

                        if (c == EOF || !flush_buff()) {
                                return BUFFER_ERROR;
                        }

                        printf("Ungueltige Eingabe, bitte versuchen Sie es erneut!\n");
                        continue; /*Benutzer wird solange nach einer Eingabe gefragt, bis diese gueltig ist*/
                }

                if (strcmp(answer, YES) && strcmp(answer, NO)) {
                        printf("Ungueltige Eingabe, bitte versuchen Sie es erneut!\n");
                        continue; /*Benutzer wird solange nach einer Eingabe gefragt, bis diese gueltig ist*/
                }

                return VALID_INPUT;
        }
}

int read_command(char *command)
{
        char c = '\0';
        int status;

        while(1) {

                printf("Bitte geben Sie ihren naechsten Befehl ein und bestaetigen Sie mit der Enter-Taste:\n");
                printf("(Fuer eine Auflistung der moeglichen Befehle koennen Sie '%s' eingeben und mit der Enter-Taste bestaetigen)\n", HELP);

                status = scanf("%"STRINGIFY_VAL(MAX_STRING_COMMAND)"s", command); /*maximale Eingabe: MAX_STRING_COMMAND-Zeichen*/

                if (status == EOF) { /*Test auf Pufferfehler, falls txt Datei eingelesen wird (nicht empfohlen)*/
                        return BUFFER_ERROR;
                }

                if (status == 0 || (c = getchar()) != '\n') {

                        if (c == EOF || !flush_buff()) {
                                return BUFFER_ERROR;
                        }

                        printf("Ungueltige Eingabe, bitte versuchen Sie es erneut!\n");
                        continue; /*Benutzer wird solange nach einer Eingabe gefragt, bis diese gueltig ist*/
                }

                if (strcmp(command, HELP) && strcmp(command, UNCOVER_FULL) && strcmp(command, UNCOVER_ABBR) && strcmp(command, FLAG_FULL) && strcmp(command, FLAG_ABBR) && strcmp(command, REMOVE_FULL) && strcmp(command, REMOVE_ABBR)) {
                        printf("Ungueltige Eingabe, bitte versuchen Sie es erneut!\n");
                        continue; /*Benutzer wird solange nach einer Eingabe gefragt, bis diese gueltig ist*/
                }

                return VALID_INPUT;
        }
}

int read_difficulty(char *difficulty)
{
        char c = '\0';
        int status;

        while (1) {

                printf("\nBitte geben Sie ihre gewuenschte Schwierigkeitsstufe (%s, %s oder %s) ein.\n", EASY, INTERMEDIATE, HARD);
                printf("Hinweis: eine hoehere Schwierigkeitsstufe bedeutet mehr Minen.\n");

                status = scanf("%"STRINGIFY_VAL(MAX_STRING_DIFFICULTY)"s", difficulty); /*maximale Eingabe: MAX_STRING_DIFFICULTY-Zeichen*/

                if (status == EOF) { /*Test auf Pufferfehler, falls txt Datei eingelesen wird (nicht empfohlen)*/
                        return BUFFER_ERROR;
                }

                if (status == 0 || (c = getchar()) != '\n') {

                        if (c == EOF || !flush_buff()) {
                                return BUFFER_ERROR;
                        }

                        printf("Ungueltige Eingabe, bitte versuchen Sie es erneut!\n");
                        continue; /*Benutzer wird solange nach einer Eingabe gefragt, bis diese gueltig ist*/
                }

                if (strcmp(difficulty, EASY) && strcmp(difficulty, INTERMEDIATE) && strcmp(difficulty, HARD)) {
                        printf("Ungueltige Eingabe, bitte geben sie die jeweilige Schwierigkeitsstufe in Grossbuchstaben ein. Versuchen Sie es erneut!\n");
                        continue; /*Benutzer wird solange nach einer Eingabe gefragt, bis diese gueltig ist*/
                }

                return VALID_INPUT;
        }
}



int read_coordinates(int rows, int columns, int coordinate[])
{
        char c = '\0', y_char = '\0';
        int status, x = 0, y = 0;

        while (1) {
                printf("\nBitte geben Sie die Koordinaten in der Form 'Zeilenname Spaltenname' z.B. 'A 1' oder 'A1' ein und bestaetigen Sie mit der Enter-Taste:\n");
                printf("Um zurueck zur Befehlseingabe zu springen geben Sie '0 0' ein.\n");

                status = scanf("%c %i", &y_char, &x);

                if (status == EOF) { /*Test auf Pufferfehler, falls txt Datei eingelesen wird (nicht empfohlen)*/
                        return BUFFER_ERROR;
                }

                if (y_char == '0' && x == 0) { /*um Koordinateneingabe abzubrechen: 0 0*/
                        if ((c = getchar()) != '\n') {
                                if (c == EOF || !flush_buff()) {
                                        return BUFFER_ERROR;
                                }
                        }
                        return ESC;
                }

                y = y_char - 'A' + 1; /*z.B. A in die Zahl 1 fuer Zeile 1 umwandeln*/

                if (status == 0 || x <= 0 || x > columns || y <= 0 || y > rows || (c = getchar()) != '\n') {

                        if (c == EOF || !flush_buff()) {
                                return BUFFER_ERROR;
                        }

                        printf("Ungueltige Eingabe, bitte versuchen Sie es erneut!\n");
                        continue; /*Benutzer wird solange nach einer Eingabe gefragt, bis diese gueltig ist*/
                }
                break;
        }

        coordinate[Y] = y;
        coordinate[X] = x;
        return VALID_INPUT;
}

int read_input(void)
{
        char c = '\0';

        if ((c = getchar()) != '\n') {
                if (c == EOF || !flush_buff()) {
                        return BUFFER_ERROR;
                }
        }

        return VALID_INPUT;
}
