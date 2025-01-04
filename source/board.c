#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

char board_mode()
{
    char mode;
        
    printf("Podaj tryb gry (e - easy, m - medium, h - hard, c - custom): ");
    mode = getc(stdin);
    //getc(stdin);
    //int result = scanf("%c", &mode);

    //printf("Tryb %c\n", mode);

    if(mode=='e' || mode=='m' || mode=='h' || mode=='c') // easy, medium, hard, custom
    {
        return mode;
    }
    else
    {
        printf("[!] Niepoprawne wyrazenie, sprobuj ponownie\n");
        return 'x';
    }
}

/*
int board_int()
{
    char temp[5];
    fgets(temp, sizeof(temp), stdin);
    int x = atoi(temp);

    //printf("%d\n", x);

    if(x>0)
    {
        return x;
    }
    else
    {
        return 0;
    }
}
*/

int board_int()
{
    char temp[3];
    fgets(temp, sizeof(temp), stdin);
    int x = atoi(temp);

    if(x>=10)
    {
        fgets(temp, sizeof(temp), stdin);
    }

    //scanf("%c");
    //printf("%d\n", x);

    if(x>0)
    {
        return x;
    }
    else
    {
        return 0;
    }
}

void board_init(board_t *board)
{
    bool correct=false;
    char temp;
    while(correct==false)
    {
        temp=board_mode();

        if(temp!='x')
        {
            correct=true;
        }
        else
        {
            //sleep(1);
            //system("@cls||clear");
            getc(stdin);
        }
    }
    
    //printf("poprawne %c\n", temp);

    int x, y, time;

    if(temp=='e')
    {
        x=9, y=9, time=10;
    }
    else if(temp=='m')
    {
        x=16, y=16, time=40;
    }
    else if(temp=='h')
    {
        x=16, y=30, time=99;
    }
    else
    {
        //scanf("%c");
        bool correct=false;
        char temp[4];

        fgets(temp, sizeof(temp), stdin);

        while(correct==false)
        {
            printf("Podaj ilosc wierszy (do dwóch znakow): ");

            x=board_int();

            if(x!=0)
            {
                correct=true;
            }
            else
            {
                printf("[!] Niepoprawne wyrazenie, sprobuj ponownie\n");
            }
        }

        correct=false;
        //fgets(temp, sizeof(temp), stdin);

        while(correct==false)
        {
            printf("Podaj ilosc kolumn (do dwóch znakow): ");

            y=board_int();

            if(y!=0)
            {
                correct=true;
            }
            else
            {
                printf("[!] Niepoprawne wyrazenie, sprobuj ponownie\n");
            }
        }

        correct=false;
        //fgets(temp, sizeof(temp), stdin);

        while(correct==false)
        {
            printf("Podaj ilosc czasu (w minutach, do dwoch znakow): ");

            time=board_int();

            if(time!=0)
            {
                correct=true;
            }
            else
            {
                printf("[!] Niepoprawne wyrazenie, sprobuj ponownie\n");
            }
        }
    }

    printf("x = %d\n", x);
    printf("y = %d\n", y);
    printf("t = %d\n", time);

    board->x=x;
    board->y=y;
    board->time=time;
    board->content=malloc(x * y * sizeof(char));
    board->state=malloc(x * y * sizeof(char));
    board->bomb_ammount=malloc(x * y * sizeof(int));

    return;
}


