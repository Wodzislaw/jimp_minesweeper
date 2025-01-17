#ifndef _SCOREBOARD_H_
#define _SCOREBOARD_H_

#define MAX_LINES 5
#define STR_SIZE 4

typedef struct
{
    char name[MAX_LINES][STR_SIZE]; // imiona graczy, po 3 litery
    int points[MAX_LINES]; // liczba punktów graczy
} scoreboard_t;

void scoreboard_get(scoreboard_t *scoreboard);

void scoreboard_edit(scoreboard_t *scoreboard, char* name, int points);

void scoreboard_out(scoreboard_t *scoreboard);

#endif