#ifndef _BOARD_H_
#define _BOARD_H_

//#include <stdio.h>

typedef struct
{
    int x; // liczba wierszy
    int y; // liczba kolumn
    int time; // czas w minutach
    char *content; // zawartosc pola
    char *state; // stan pola
} board_t;

void board_init(board_t *board);



#endif