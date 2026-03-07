#include "leaderboard.h"
#include "readandinput.h"

int read_leaderboard_entries(Entry leaderboard[], char *difficulty, int *number_of_entries)
{
        FILE *file;
        int status;

        /*unterschiedliche Bestenlisten fuer unteschiedliche Schwierigkeitsstufen*/
        if (!strcmp(difficulty, EASY)) {
                file = fopen("bestenliste_einfach.txt", "r");
        } else if (!strcmp(difficulty, INTERMEDIATE)) {
                file = fopen("bestenliste_mittel.txt", "r");
        } else {
                file = fopen("bestenliste_schwer.txt", "r");
        }

        if (file == NULL) {
                return FAILURE;
        }

        while(*number_of_entries < MAX_ENTRIES_LEADERBOARD) {

                status = fscanf(file, "%s %lf %i", leaderboard[*number_of_entries].name, &leaderboard[*number_of_entries].seconds, &leaderboard[*number_of_entries].number_of_commands);

                if (status == EOF) { /*Test auf Pufferfehler*/
                        fclose(file);
                        return BUFFER_ERROR;
                }

                if (status < 3) {
                        fclose(file);
                        return FAILURE;
                }
        
                ++(*number_of_entries);
        }

        fclose(file);
        return SUCCESS;
}

void swap_entries(char *leaderboard_name, double *leaderboard_seconds, int *leaderboard_number_of_commands, char *name, double *seconds_since_start, int *number_of_commands)
{
        char temp_name[MAX_STRING_NAME + 1];
        double temp_seconds;
        int temp_number_of_commands;

        strcpy(temp_name, leaderboard_name); /*Tausch des Namens*/
        strcpy(leaderboard_name, name);
        strcpy(name, temp_name);

        temp_seconds = *leaderboard_seconds; /*Tausch der benoetigten Sekunden*/
        *leaderboard_seconds = *seconds_since_start;
        *seconds_since_start = temp_seconds;

        temp_number_of_commands = *leaderboard_number_of_commands; /*Tausch der benoetigten Anzahl an Befehlen*/
        *leaderboard_number_of_commands = *number_of_commands;
        *number_of_commands = temp_number_of_commands;
}

int add_to_leaderboard(int number_of_commands, double seconds_since_start, char *difficulty, char name[])
{
        FILE *file;
        int status, i, number_of_entries = 0;
        Entry leaderboard[MAX_ENTRIES_LEADERBOARD];
        
        status = read_leaderboard_entries(leaderboard, difficulty, &number_of_entries);

        /*wenn BUFFER_ERROR: number_of_entries ist nicht die maximale Anzahl, die Liste ist kuerzer und der neue Eintrag wird eingefuegt*/

        if (status == FAILURE) { /*die Bestenliste existiert noch nicht*/
                /*unterschiedliche Bestenlisten fuer unteschiedliche Schwierigkeitsstufen*/
                if (!strcmp(difficulty, EASY)) {
                        file = fopen("bestenliste_einfach.txt", "a"); /*a erstellt eine neue Datei und fuegt unten Eintraege hinzu*/
                } else if (!strcmp(difficulty, INTERMEDIATE)) {
                        file = fopen("bestenliste_mittel.txt", "a");
                } else {
                        file = fopen("bestenliste_schwer.txt", "a");
                }

                fprintf(file, "%s %.0f %i\n", name, seconds_since_start, number_of_commands);

                fclose(file);

                return SUCCESS;
        }

        if (number_of_entries == MAX_ENTRIES_LEADERBOARD) {
                if (leaderboard[number_of_entries - 1].seconds < seconds_since_start) { /*wenn schlechter als schlechtester in Bestenliste: kein Vergleich und keine Aenderung*/
                        return SUCCESS;
                } else if (leaderboard[number_of_entries - 1].seconds == seconds_since_start) {
                        if (leaderboard[number_of_entries - 1].number_of_commands < number_of_commands) {
                                return SUCCESS;
                        }
                }
        }

        /*unterschiedliche Bestenlisten fuer unteschiedliche Schwierigkeitsstufen*/
        if (!strcmp(difficulty, EASY)) {
                file = fopen("bestenliste_einfach.txt", "w"); /*w um die alte Datei zu loeschen und zu ueberschreiben*/
        } else if (!strcmp(difficulty, INTERMEDIATE)) {
                file = fopen("bestenliste_mittel.txt", "w");
        } else {
                file = fopen("bestenliste_schwer.txt", "w");
        }

        if (file == NULL) {
                return FAILURE;
        }

        for (i = 0; i < number_of_entries; i++) { /*alle vorhandenen Eintraege mit dem neuen Eintrag vergleichen*/

                if (leaderboard[i].seconds > seconds_since_start) { /*weniger Sekunden = besser*/

                        /*Eintraege tauschen und sich den alten Eintrag merken*/
                        swap_entries(leaderboard[i].name, &leaderboard[i].seconds, &leaderboard[i].number_of_commands, name, &seconds_since_start, &number_of_commands);

                } else if (leaderboard[i].seconds == seconds_since_start) { /*wenn gleiche Sekundenanzahl zaehlt die Anzahl an Befehlen*/

                        if (leaderboard[i].number_of_commands > number_of_commands) { /*weniger Befehle = besser*/

                                swap_entries(leaderboard[i].name, &leaderboard[i].seconds, &leaderboard[i].number_of_commands, name, &seconds_since_start, &number_of_commands);
                                
                        } else if (leaderboard[i].number_of_commands == number_of_commands) { /*wenn gleiche Anzahl an Befehlen zaehlt die Sortierung des Namens*/

                                if (strcmp(name, leaderboard[i].name) < 0) {

                                        swap_entries(leaderboard[i].name, &leaderboard[i].seconds, &leaderboard[i].number_of_commands, name, &seconds_since_start, &number_of_commands);
                                }
                        }
                }

                fprintf(file, "%s %.0f %i\n", leaderboard[i].name, leaderboard[i].seconds, leaderboard[i].number_of_commands); /*speichere die Eintraege von bester zu schlechtester in der Datei*/
        }

        if (number_of_entries < MAX_ENTRIES_LEADERBOARD) { /*wenn weniger Eintraege in der Liste als die maximale Anzahl an Eintraegen, soll der letzte Eintrag gespeichert werden*/

                fprintf(file, "%s %.0f %i\n", name, seconds_since_start, number_of_commands);
        }

        fclose(file);

        return SUCCESS;
}

int print_leaderboard(char *difficulty)
{
        Entry leaderboard[MAX_ENTRIES_LEADERBOARD];
        int  i, status, number_of_entries = 0;

        status = read_leaderboard_entries(leaderboard, difficulty, &number_of_entries);

        /*status == Buffer_Error bedeutet nur weniger Eintraege als erwartet: vorhandene Eintraege trotzdem ausgeben, kein Abbruch*/

        if (status == FAILURE) { /*Datei existiert nicht: Abbruch*/
                return FAILURE;
        }       

        printf("\nBestenliste der Schwierigkeitsstufe %s:\n", difficulty);
        printf("| %-12s | %-8s | %-8s |\n", "Name", "Sekunden", "Befehle");
        printf("|--------------|----------|----------|\n");

        for (i = 0; i < number_of_entries; i++) {
                printf("| %-12s | %-8.0f | %-8d |\n", leaderboard[i].name, leaderboard[i].seconds, leaderboard[i].number_of_commands);
        }

        return SUCCESS;
}

int leaderboard(int number_of_commands, double seconds_since_start, char *difficulty, int result)
{

        char name[MAX_STRING_NAME + 1]; /*MAX_STRING_NAME-Zeichen + binaere Null*/
        char answer[MAX_STRING_YES_OR_NO + 1];
        int status;


        if (result == WIN) { /*nur Jemand, der gewonnen hat darf auf die Bestenliste*/

                read_name(name);

                status = add_to_leaderboard(number_of_commands, seconds_since_start, difficulty, name);

                if (status == FAILURE) {
                        return FAILURE;
                }
        }

        printf("\nMoechten Sie sich die ersten %i Eintraege der Bestenliste anzeigen lassen?\n", MAX_ENTRIES_LEADERBOARD);
        status = read_yes_or_no(answer);
        if (status == BUFFER_ERROR) {
                return BUFFER_ERROR;
        }

        if (!strcmp(answer, YES)) { /*wenn die Antwort "ja" war*/
                status = print_leaderboard(difficulty);
                if (status == FAILURE) {
                        return FAILURE;
                }
                return SUCCESS;
        }

        if (!strcmp(answer, NO)) { /*wenn die Antwort "nein" war*/
                return SUCCESS;
        }

        return FAILURE; /*falls ein Fehler auftritt*/

}
