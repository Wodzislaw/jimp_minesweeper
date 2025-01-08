#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <stdbool.h>

#include "board.h"

int main()
{
    system("@cls||clear");

    board_t board;
    board_init(&board);

    printf("\n");
    printf("x = %d\n", board.x);
    printf("y = %d\n", board.y);
    printf("t = %d\n", board.time);

    board_fill(&board);
    board_out(&board);

    return EXIT_SUCCESS;
}