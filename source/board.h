#ifndef _BOARD_H_
#define _BOARD_H_

//#include <stdio.h>

typedef struct
{
    int x; // liczba wierszy
    int y; // liczba kolumn
    int time; // czas w minutach
    int mult; // mnożnik punktów
    char *content; // zawartosc pola
    char *state; // stan pola
    int *bomb_ammount; // ilosc bomb w obszarze 3x3
    char* game; // win, lose albo ongoing
} board_t;

void board_init(board_t *board);

void board_state_fill(board_t *board);

void board_content_fill(board_t *board);

void board_bomb_ammount_fill(board_t *board);

void board_state_out(board_t *board);

void board_content_out(board_t *board);

void board_bomb_ammount_out(board_t *board);

void board_interact(board_t *board);

#endif