#ifndef _BOARD_H_
#define _BOARD_H_

//#include <stdio.h>

typedef struct
{
    int x; // liczba wierszy
    int y; // liczba kolumn
    int current_x; // obecna pozycja x
    int current_y; // obecna pozycja y
    int bombs; // ilość bomb na planszy
    int mult; // mnożnik punktów
    char *content; // zawartosc pola
    char *state; // stan pola
    int *bomb_ammount; // ilosc bomb w obszarze 3x3
    int game; // 0 - win, 1 - lose, 2 - ongoing
    int first; // pierwsza interakcja z planszą
} board_t;

void board_init(board_t *board);

void board_state_fill(board_t *board);

void board_content_fill(board_t *board);

// void board_content_fill2(board_t *board);

void board_bomb_ammount_fill(board_t *board);

void board_state_out(board_t *board);

void board_content_out(board_t *board);

void board_bomb_ammount_out(board_t *board);

void board_interact(board_t *board);

void board_shatter(board_t *board);

void board_check_win(board_t *board);

void board_lose_out(board_t *board);

#endif