#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//#include <stdbool.h>

#include "board.h"
#include "scoreboard.h"

int main(int argc, char **argv)
{
    int opt, cheat=0;

    while((opt=getopt(argc, argv, "c")) != -1)
    {
        switch(opt)
        {
            case 'c':
                cheat=1;
                break;
            default:
                cheat=0;
                break;
        }

    }

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

    //board_content_fill(&board);
    //board_content_out(&board);

    //board_bomb_ammount_fill(&board);
    //board_bomb_ammount_out(&board);
    
    while(board.game==2)
    {
        system("@cls||clear");

        //printf("%d\n", board.bombs);

        board_state_out(&board);

        if(cheat==1 && board.actual_first==0)
        {
            board_content_out(&board);
        }

        board_interact(&board);

        if(board.actual_first==1)
        {
            board_content_fill(&board);
            board_bomb_ammount_fill(&board);

            if(board.bomb_ammount[board.first_position]==0)
            {
                board_shatter(&board);
            }

            board.actual_first=0;
        }
        else
        {
            if(board.game==2)
            {
                board_check_win(&board);
            }
        }
    }
    
    system("@cls||clear");

    //printf("%d\n", board.game);
    if(board.game==0)
    {
        printf("[WYGRANA]");
    }
    else
    {
        printf("[PRZEGRANA]");
    }

    printf(" - Punkty końcowe: %d\n\n", board.points);

    board_end_out(&board);

    if(cheat==0)
    {
        char temp[4];

        printf("\nPodaj imię gracza (3 litery): ");
        fgets(temp, sizeof(temp), stdin);

        printf("\n");

        scoreboard_t scoreboard;

        scoreboard_get(&scoreboard);
        scoreboard_edit(&scoreboard, temp, board.points);
        scoreboard_out(&scoreboard);
    }

    return EXIT_SUCCESS;
}