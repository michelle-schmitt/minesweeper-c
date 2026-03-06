#ifndef CONST_H_INCLUDED
#define CONST_H_INCLUDED

#ifdef _WIN32
    #include <windows.h>
    #define CLEAR "cls"
#else
    #include <unistd.h>
    #define CLEAR "clear"
#endif

/*Einfache Wartbarkeit durch Konstanten in einer Header-Datei:*/
#define MAX_SIZE_ROWS 10 /*um in der Eingabeaufforderung unten die Input-Aufforderungen zu sehen*/
#define MAX_SIZE_COL 25
#define STANDARD_SIZE 5
#define MAX_ENTRIES_LEADERBOARD 10
#define MAX_STRING_COMMAND 7 /*max string: uncover*/
#define MAX_STRING_DIFFICULTY 12 /*max string: intermediate*/
#define MAX_STRING_NAME 10
#define MAX_STRING_YES_OR_NO 4 /*max string (ja oder nein): nein*/
#define DIMENSIONS 2 /*zweidimensionaler Raum fuer Koordinaten*/
#define NOT_UNCOVERED -1
#define MINE -2
#define FLAG -3
#define Y 0
#define X 1
#define LOST -3
#define WIN 3
#define FAILURE 0
#define SUCCESS 1
#define BUFFER_ERROR -2
#define VALID_INPUT 1
#define ESC -9

#define EASY "EASY"
#define PERCENTAGE_EASY 0.1
#define INTERMEDIATE "INTERMEDIATE"
#define PERCENTAGE_INTERMEDIATE 0.15
#define HARD "HARD"
#define PERCENTAGE_HARD 0.2

#define HELP "help"
#define UNCOVER_FULL "uncover"
#define UNCOVER_ABBR "u"
#define FLAG_FULL "flag"
#define FLAG_ABBR "f"
#define REMOVE_FULL "remove"
#define REMOVE_ABBR "r"
#define YES "ja"
#define NO "nein"

/*Makros:*/
#define STRINGIFY(x) #x
#define STRINGIFY_VAL(x) STRINGIFY(x)

/*Farben sind nicht plattformunabhaengig!*/
#define DEFAULT() printf("\033[0m")
#define GREEN() printf("\033[0;32m")
#define YELLOW() printf("\033[0;33m")
#define PURPLE() printf("\033[0;35m")
#define RED() printf("\033[0;31m")
#define CYAN() printf("\033[0;36m")

typedef struct Entry {
        char name[MAX_STRING_NAME + 1];
        double seconds;
        int number_of_commands;
} Entry;

#endif
