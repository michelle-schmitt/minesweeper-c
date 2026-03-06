#include <time.h>
#include <ctype.h>

#include "leaderboard.h"
#include "init.h"
#include "mines.h"
#include "gameloop.h"
#include "printf.h"
#include "readandinput.h"

/*weitere Ideen bzw. To-Do:
- Leaderboardliste effizienter vergleichen/tauschen (z.B. gar durchgehen, wenn schlechter als letzter Eintrag und Vergleich anders wie in Kap. 11 gestalten)
- Standardgröße des Spielfelds überlegen
- Länge der Bestenliste überlegen + ob Spielfeldgröße angezeigt/wichtig
- Spiel testen (Eingaben, Ausgaben, Bestenliste, Berechnungen, ...)
- Benutzerführung nochmal ansehen ob gut
- Header Dateien und Übersetzungseinheiten
- symbolische Konstanten und deren Werte überarbeiten?
- Code noch effizienter/übersichtlicher machen?
- Pufferfehler beachten oder nicht? (außer bei der Bestenliste)
- Lösung für Plattformabhängige Dinge*/



int main(int argc, char *argv[])
{
        int rows, columns, i, j, status, result, number_of_commands = 0;
        int **field, **mines;
        char *command, *difficulty;
        time_t start_time, end_time;
        double seconds_since_start;

        srand(time(NULL));

        if (argc != 3) {
                printf("\nUngueltige Anzahl an Kommandozeilenparameter! Es wird die Standardgroesse %ix%i fuer das Spielfeld verwendet.\n", STANDARD_SIZE, STANDARD_SIZE);
                rows = columns = STANDARD_SIZE;
        } else {
                rows = atoi(argv[1]);
                columns = atoi(argv[2]);

                if (rows < 2 || columns < 2) { /*wenn das Spielfeld zu klein ist*/
                        printf("\nUngueltige Eingabe. Das Spielfeld darf minimal 2x2 sein.\n"),
                        printf("Es wird stattdessen die Standardgroesse %ix%i fuer das Spielfeld verwendet.\n", STANDARD_SIZE, STANDARD_SIZE);
                        rows = columns = STANDARD_SIZE;
                }
                
                
                if (rows > MAX_SIZE || columns > MAX_SIZE) { /*wenn das Spielfeld zu gross ist*/
                        printf("\nUngueltige Eingabe. Das Spielfeld darf maximal %ix%i sein.\n", MAX_SIZE, MAX_SIZE),
                        printf("Es wird stattdessen die maximale Groesse %ix%i fuer das Spielfeld verwendet.\n", MAX_SIZE, MAX_SIZE);
                        rows = columns = MAX_SIZE;
                }

                for (i = 0; argv[1][i] != '\0'; i++) { /*Test, ob ganze Zahl fuer die Hoehe eingegeben wurde*/
                        if(!isdigit(argv[1][i])) {
                                printf("\nUngueltige Eingabe: Die Hoehe des Spielfelds muss eine positive ganze Zahl groeser 1 sein!\n");
                                printf("Es wird stattdessen die Standardhoehe %i verwendet.\n", STANDARD_SIZE);
                                rows = STANDARD_SIZE;
                        }
                }

                for (j = 0; argv[2][j] != '\0'; j++) { /*Test, ob ganze Zahl fuer die Breite eingegeben wurde*/
                        if(!isdigit(argv[2][j])) {
                                printf("\nUngueltige Eingabe: Die Breite des Spielfelds muss eine positive ganze Zahl groeser 1 sein!\n");
                                printf("Es wird stattdessen die Standardbreite %i verwendet.\n", STANDARD_SIZE);
                                columns = STANDARD_SIZE;
                        }
                }
        }

        minesweeper_instructions();


        while (1) { /*Schleife nur dazu da, um über break das restliche Programm bei einer Fehlermeldung nicht weiter auszufuehren*/

                /*Speicherplatz fuer alle wichtigen Pointer reservieren, um diesen spaeter gesammelt wieder freizugeben:*/
                field = field_init(rows, columns);
                if (field == NULL) {
                        printf("Fehler: nicht genuegend Speicherplatz vorhanden!");
                        result = FAILURE; /*kein return, um den Speicherplatz unten gesammelt wieder freizugeben anstatt vor jedem return*/
                        break; /*um zur Speicherfreigabe zu springen, ohne das Programm fortzusetzen*/
                }

                mines = field_init_zeroes(rows, columns);
                if (mines == NULL) {
                        printf("Fehler: nicht genuegend Speicherplatz vorhanden!");
                        result = FAILURE;
                        break;
                }

                difficulty = malloc((MAX_STRING_DIFFICULTY + 1) * sizeof(char)); /*Speicher reservieren fuer MAX_STRING_DIFFICULTY Zeichen + binaere NULL*/
                if (difficulty == NULL) {
                        printf("Fehler: nicht genuegend Speicherplatz vorhanden!");
                        result = FAILURE;
                        break;
                }

                status = read_difficulty(difficulty); /*Schwierigkeit abfragen*/
                if (status == BUFFER_ERROR) {
                        result = FAILURE;
                        break;
                }

                command = malloc((MAX_STRING_COMMAND + 1) * sizeof(char)); /*Speicher reservieren fuer MAX_STRING_COMMAND Zeichen + binaere NULL*/
                if (command == NULL) {
                        printf("Fehler: nicht genuegend Speicherplatz vorhanden!");
                        result = FAILURE;
                        break;
                }

                /*Spiel starten und Fehlermeldungen testen*/
                time(&start_time); /*Starten der Zeitmessung, da nun das Spiel begonnen wird*/
                status = minesweeper_game(rows, columns, field, mines, command, difficulty, &number_of_commands);
                time(&end_time); /*Beenden der Zeitmessung, da das Spiel beendet wurde*/
                seconds_since_start = difftime(end_time, start_time);

                if(status == BUFFER_ERROR) {
                        printf("Pufferfehler!");
                        result = FAILURE;
                        break;
                }

                if (status == LOST) {
                        boom();
                }
        
                if (status == WIN) {
                        win();
                }

                printf("\nBenoetigte Befehle: %i\n", number_of_commands);
                printf("Spielzeit: %.1f Sekunden\n", seconds_since_start);

                status = leaderboard(number_of_commands, seconds_since_start, difficulty, status);  /*status an Funktion uebergeben ist WIN oder LOST (siehe oben)*/

                if (status == FAILURE) {
                        printf("\nFehler beim Oeffnen der Datei fuer die Bestenliste!\n");
                }

                result = SUCCESS;
                break;
        }

        if (field != NULL) { /*Speicherplatz nur freigeben, wenn die Allokation funktioniert hat*/
                free_field(field, rows);
        }

        if (mines != NULL) {
                free_field(mines, rows);
        }

        if (command != NULL) {
                free(command);
        }

        if (difficulty != NULL) {
                free(difficulty);
        }

        return result;
}