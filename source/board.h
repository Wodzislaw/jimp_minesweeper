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
    int points; // ilość punktów
    char *content; // zawartosc pola
    char *state; // stan pola
    int *bomb_ammount; // ilosc bomb w obszarze 3x3
    int game; // 0 - win, 1 - lose, 2 - ongoing
    int first; // pierwsza interakcja z planszą (dla poprawnego wpisywania)
    int actual_first; // pierwsza interakcja z planszą (usunięcia pola)
    int first_position; // pozycja pierwszego usunięcia pola
} board_t;

void board_init(board_t *board); // inicjalizacja struktury

void board_state_fill(board_t *board); // wypełnienie tablicy state

void board_content_fill(board_t *board); // wypełnienie tablicy content

void board_bomb_ammount_fill(board_t *board); // wypełnienie tablicy bomb_ammount

void board_state_out(board_t *board); // wypisanie zawartości tablicy state

void board_content_out(board_t *board); // wypisanie zawartości tablicy content

void board_bomb_ammount_out(board_t *board); // wypisanie zawartości tablicy bomb_ammount

void board_interact(board_t *board); // wejście w interakcję z planszą

void board_shatter(board_t *board); // czyszczenie się sąsiednich pól zerowych

void board_check_win(board_t *board); // sprawdzenie warunków wygranej

void board_end_out(board_t *board); // wypisanie planszy z widocznymi bombami oraz stanem planszy

#endif