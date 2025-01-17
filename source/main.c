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
    //bool first=true;

    /*
    printf("\n");
    printf("x = %d\n", board.x);
    printf("y = %d\n", board.y);
    printf("t = %d\n", board.time);
    */

    board_state_fill(&board);
    //board_state_out(&board);

    board_content_fill(&board);
    //board_content_out(&board);

    board_bomb_ammount_fill(&board);
    //board_bomb_ammount_out(&board);
    
    while(board.game==2)
    {
        system("@cls||clear");

        //printf("%d\n", board.bombs);

        board_state_out(&board);

        board_interact(&board);

        if(board.game==2)
        {
            board_check_win(&board);
        }
    }
    
    printf("%d\n", board.game);

    if(board.game==1)
    {
        board_lose_out(&board);
    }

    // board_lose_out(&board);

    return EXIT_SUCCESS;
}