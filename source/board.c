#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

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
        printf("[!]: Niepoprawne wyrazenie, sprobuj ponownie\n");
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

    int x, y, time, mult, field;

    if(temp=='e')
    {
        x=9, y=9, time=10, mult=1;
        field=x*y;
    }
    else if(temp=='m')
    {
        x=16, y=16, time=40, mult=2;
        field=x*y;
    }
    else if(temp=='h')
    {
        x=16, y=30, time=99, mult=3;
        field=x*y;
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
                printf("[!]: Niepoprawne wyrazenie, sprobuj ponownie\n");
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
                printf("[!]: Niepoprawne wyrazenie, sprobuj ponownie\n");
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

        field=x*y;

        if(field<=81)
        {
            mult=1;
        }
        else if(field<=256)
        {
            mult=2;
        }
        else if(field<=480)
        {
            mult=3;
        }
        else
        {
            mult=4;
        }
    }


    /*
    printf("x = %d\n", x);
    printf("y = %d\n", y);
    printf("t = %d\n", time);
    printf("f = %d\n", field);
    printf("m = %d\n", mult);
    */

    //int bombs=field/5;

    //printf("b = %d\n", bombs);

    board->x=x;
    board->y=y;
    board->time=time;
    board->mult=mult;
    board->content=malloc(x * y * sizeof(char));
    board->state=malloc(x * y * sizeof(char));
    board->bomb_ammount=malloc(x * y * sizeof(int));
    board->game=2;

    if(temp=='c')
    {
        board->first=0;
    }
    else
    {
        board->first=1;
    }

    return;
}

void board_state_fill(board_t *board)
{
    int x=board->x;
    int y=board->y;

    for(int i=0; i<x; i++)
    {
        for(int j=0; j<y; j++)
        {
            board->state[j+i*y]='#';
        }
    }
}

void board_content_fill(board_t *board)
{
    int field=board->x * board->y;

    srand(time(NULL));
    int random;
    for(int i=0; i<field; i++)
    {
        random=rand() % 100 + 1;
        
        if(random<=15)
        {
            board->content[i]='B';
        }
        else
        {
            board->content[i]='N';
        }
    }
}

/*
void board_bomb_ammount_fill(board_t *board)
{
    int x=board->x;
    int y=board->y;
    int field=x*y;

    for(int i=0; i<field; i++)
    {
        if(i%y!=0)
        {
            if(i-y-1 >= 0)
            {
                board->bomb_ammount[i]++;
            }

            if(i-1 >= 0)
            {
                board->bomb_ammount[i]++;
            }

            if(i+y-1 < field)
            {
                board->bomb_ammount[i]++;
            }
        }


        if(i-y >= 0)
        {
            board->bomb_ammount[i]++;
        }

        if(i+y < field)
        {
            board->bomb_ammount[i]++;
        }


        if(i%(y-1)!=0)
        {
            if(i-y+1 >= 0)
            {
                board->bomb_ammount[i]++;
            }

            if(i+1 < field)
            {
                board->bomb_ammount[i]++;
            }

            if(i+y+1 < field)
            {
                board->bomb_ammount[i]++;
            }
        }
    }
}
*/

void board_bomb_ammount_fill(board_t *board)
{
    int x=board->x;
    int y=board->y;
    int pos;

    for(int i=0; i<x; i++)
    {
        for(int j=0; j<y; j++)
        {
            pos=i*y+j;

            if(i==0)
            {
                if(j==0)
                {
                    if(board->content[pos+1]=='B')
                    {
                        board->bomb_ammount[pos]++;
                    }

                    if(board->content[pos+y]=='B')
                    {
                        board->bomb_ammount[pos]++;
                    }

                    if(board->content[pos+y+1]=='B')
                    {
                        board->bomb_ammount[pos]++;
                    }
                }
                else if(j==y-1)
                {
                    if(board->content[pos-1]=='B')
                    {
                        board->bomb_ammount[pos]++;
                    }

                    if(board->content[pos+y]=='B')
                    {
                        board->bomb_ammount[pos]++;
                    }

                    if(board->content[pos+y-1]=='B')
                    {
                        board->bomb_ammount[pos]++;
                    }
                }
                else
                {
                    if(board->content[pos-1]=='B')
                    {
                        board->bomb_ammount[pos]++;
                    }

                    if(board->content[pos+1]=='B')
                    {
                        board->bomb_ammount[pos]++;
                    }

                    if(board->content[pos+y-1]=='B')
                    {
                        board->bomb_ammount[pos]++;
                    }

                    if(board->content[pos+y]=='B')
                    {
                        board->bomb_ammount[pos]++;
                    }

                    if(board->content[pos+y+1]=='B')
                    {
                        board->bomb_ammount[pos]++;
                    }
                }
            }
            else if(i==x-1)
            {
                if(j==0)
                {
                    if(board->content[pos+1]=='B')
                    {
                        board->bomb_ammount[pos]++;
                    }

                    if(board->content[pos-y]=='B')
                    {
                        board->bomb_ammount[pos]++;
                    }

                    if(board->content[pos-y+1]=='B')
                    {
                        board->bomb_ammount[pos]++;
                    }
                }
                else if(j==y-1)
                {
                    if(board->content[pos-1]=='B')
                    {
                        board->bomb_ammount[pos]++;
                    }

                    if(board->content[pos-y]=='B')
                    {
                        board->bomb_ammount[pos]++;
                    }

                    if(board->content[pos-y-1]=='B')
                    {
                        board->bomb_ammount[pos]++;
                    }
                }
                else
                {
                    if(board->content[pos-1]=='B')
                    {
                        board->bomb_ammount[pos]++;
                    }

                    if(board->content[pos+1]=='B')
                    {
                        board->bomb_ammount[pos]++;
                    }

                    if(board->content[pos-y-1]=='B')
                    {
                        board->bomb_ammount[pos]++;
                    }

                    if(board->content[pos-y]=='B')
                    {
                        board->bomb_ammount[pos]++;
                    }

                    if(board->content[pos-y+1]=='B')
                    {
                        board->bomb_ammount[pos]++;
                    }
                }
            }
            else
            {
                if(j==0)
                {
                    if(board->content[pos+1]=='B')
                    {
                        board->bomb_ammount[pos]++;
                    }

                    if(board->content[pos+y]=='B')
                    {
                        board->bomb_ammount[pos]++;
                    }

                    if(board->content[pos+y+1]=='B')
                    {
                        board->bomb_ammount[pos]++;
                    }

                    if(board->content[pos-y]=='B')
                    {
                        board->bomb_ammount[pos]++;
                    }

                    if(board->content[pos-y+1]=='B')
                    {
                        board->bomb_ammount[pos]++;
                    }
                }
                else if(j==y-1)
                {
                    if(board->content[pos-1]=='B')
                    {
                        board->bomb_ammount[pos]++;
                    }

                    if(board->content[pos+y]=='B')
                    {
                        board->bomb_ammount[pos]++;
                    }

                    if(board->content[pos+y-1]=='B')
                    {
                        board->bomb_ammount[pos]++;
                    }

                    if(board->content[pos-y]=='B')
                    {
                        board->bomb_ammount[pos]++;
                    }

                    if(board->content[pos-y-1]=='B')
                    {
                        board->bomb_ammount[pos]++;
                    }
                }
                else
                {
                    if(board->content[pos-1]=='B')
                    {
                        board->bomb_ammount[pos]++;
                    }

                    if(board->content[pos+1]=='B')
                    {
                        board->bomb_ammount[pos]++;
                    }

                    if(board->content[pos+y-1]=='B')
                    {
                        board->bomb_ammount[pos]++;
                    }

                    if(board->content[pos+y]=='B')
                    {
                        board->bomb_ammount[pos]++;
                    }

                    if(board->content[pos+y+1]=='B')
                    {
                        board->bomb_ammount[pos]++;
                    }

                    if(board->content[pos-y-1]=='B')
                    {
                        board->bomb_ammount[pos]++;
                    }

                    if(board->content[pos-y]=='B')
                    {
                        board->bomb_ammount[pos]++;
                    }

                    if(board->content[pos-y+1]=='B')
                    {
                        board->bomb_ammount[pos]++;
                    }
                }
            }

            if(board->content[pos]=='B')
            {
                board->bomb_ammount[pos]++;
            }

        }
    }
}

void board_state_out(board_t *board)
{
    int x=board->x;
    int y=board->y;

    printf("     ");

    for(int i=0; i<y; i++)
    {
        if(i+1<10)
        {
            printf(" ");
        }

        printf("%d ", i+1);
    }

    printf("  y\n\n");

    for(int i=0; i<x; i++)
    {
        if(i+1<10)
        {
            printf(" ");
        }

        printf("%d   ", i+1);

        for(int j=0; j<y; j++)
        {
            if(board->state[j+i*y]==' ' && board->bomb_ammount[j+i*y]!=0)
            {
                printf(" %d ", board->bomb_ammount[j+i*y]);
            }
            else
            {
                printf(" %c ", board->state[j+i*y]);
            }
        }

        printf("\n");
    }

    printf("\n x\n");
}

void board_content_out(board_t *board)
{
    int x=board->x;
    int y=board->y;

    printf("     ");

    for(int i=0; i<y; i++)
    {
        if(i+1<10)
        {
            printf(" ");
        }

        printf("%d ", i+1);
    }

    printf("  y\n\n");

    for(int i=0; i<x; i++)
    {
        if(i+1<10)
        {
            printf(" ");
        }

        printf("%d   ", i+1);

        for(int j=0; j<y; j++)
        {
            printf(" %c ", board->content[j+i*y]);
        }

        printf("\n");
    }

    printf("\n x\n");
}

void board_bomb_ammount_out(board_t *board)
{
    int x=board->x;
    int y=board->y;

    printf("     ");

    for(int i=0; i<y; i++)
    {
        if(i+1<10)
        {
            printf(" ");
        }

        printf("%d ", i+1);
    }

    printf("  y\n\n");

    for(int i=0; i<x; i++)
    {
        if(i+1<10)
        {
            printf(" ");
        }

        printf("%d   ", i+1);

        for(int j=0; j<y; j++)
        {
            printf(" %d ", board->bomb_ammount[j+i*y]);
        }

        printf("\n");
    }

    printf("\n x\n");
}

void board_interact(board_t *board)
{
    char function;
    int x, y;
    bool correct=false;
        
    //printf("Podaj operację którą chcesz wykonać (f - flaga, r - odsłoń pole): ");
    //getc(stdin);
    //function=getc(stdin);
    
    while(correct==false)
    {
        printf("Podaj operację którą chcesz wykonać (f - flaga, r - odsłoń pole): ");

        if(board->first==1)
        {
            getc(stdin);
            board->first=0;
        }
        //getc(stdin);
        function=getc(stdin);

        if(function=='f' || function=='r')
        {
            correct=true;
        }
        else
        {
            printf("[!]: Niepoprawne wyrażenie, spróbuj ponownie\n");
        }
    }

    char temp[4];

    fgets(temp, sizeof(temp), stdin);

    correct=false;

    while(correct==false)
    {
        printf("Podaj x: ");
        x=board_int();

        if(x!=0 && x<=board->x)
        {
            correct=true;
        }
        else
        {
            printf("[!]: Niepoprawne wyrażenie, spróbuj ponownie\n");
        }
    }

    correct=false;

    while(correct==false)
    {
        printf("Podaj y: ");
        y=board_int();

        if(y!=0 && y<=board->y)
        {
            correct=true;
        }
        else
        {
            printf("[!]: Niepoprawne wyrażenie, spróbuj ponownie\n");
        }
    }

    //fgets(temp, sizeof(temp), stdin);

    board->current_x=x-1;
    board->current_y=y-1;

    /*
    printf("%c\n", function);
    printf("%d\n", x);
    printf("%d\n", y);
    */

    int pos=(x-1)*board->y + (y-1);

    //printf("%d\n", pos);

    if(function=='f')
    {
        //board->last_action='f';

        if(board->state[pos]=='#')
        {
            board->state[pos]='f';
        }
        else if(board->state[pos]=='f')
        {
            board->state[pos]='#';
        }
    }
    else
    {
        //board->last_action='r';

        if(board->content[pos]=='B')
        {
            board->game=1;
        }
        else
        {
            board->state[pos]=' ';

            if(board->bomb_ammount[pos]==0)
            {
                board_shatter(board);
            }
        }
    }


}

void board_shatter(board_t *board)
{
    // printf("%d, %d\n", board->current_x, board->current_y);

    int pos=board->current_x * board->y + board->current_y;
    int current_pos;

    //printf("%d, %d, %d\n", board->current_x, board->current_y, pos);

    bool up=true, left=true, right=true, down=true;
    bool end=false;

    for(int i=0; i<board->x; i++)
    {
        for(int j=0; j<board->y; j++)
        {
            current_pos=i*board->y + j;

            if(current_pos==pos)
            {
                if(j==0)
                {
                    left=false;
                }

                if(j==board->y-1)
                {
                    right=false;
                }

                if(i==0)
                {
                    up=false;
                }

                if(i==board->x-1)
                {
                    down=false;
                }

                if(left==true)
                {
                    if(board->bomb_ammount[current_pos-1]==0 && board->state[current_pos-1]=='#')
                    {
                        board->state[current_pos-1]=' ';

                        board->current_x=i;
                        board->current_y=j-1;

                        board_shatter(board);
                    }
                }

                if(right==true)
                {
                    if(board->bomb_ammount[current_pos+1]==0 && board->state[current_pos+1]=='#')
                    {
                        board->state[current_pos+1]=' ';

                        board->current_x=i;
                        board->current_y=j+1;

                        board_shatter(board);
                    }
                }

                if(up==true)
                {
                    if(board->bomb_ammount[current_pos - board->y]==0 && board->state[current_pos - board->y]=='#')
                    {
                        board->state[current_pos-board->y]=' ';

                        board->current_x=i-1;
                        board->current_y=j;

                        board_shatter(board);
                    }
                }

                if(down==true)
                {
                    if(board->bomb_ammount[current_pos + board->y]==0 && board->state[current_pos + board->y]=='#')
                    {
                        board->state[current_pos+board->y]=' ';

                        board->current_x=i+1;
                        board->current_y=j;

                        board_shatter(board);
                    }
                }

                end=true;
                break;
            }
        }
        if(end==true)
        {
            break;
        }
    }

    if(left==true)
    {
        board->state[current_pos-1]=' ';
    }

    if(right==true)
    {
        board->state[current_pos+1]=' ';
    }

    if(up==true)
    {
        board->state[current_pos-board->y]=' ';
    }

    if(down==true)
    {
        board->state[current_pos+board->y]=' ';
    }

}

void board_check_win(board_t *board)
{
    int x=board->x;
    int y=board->y;
    int size=x*y;

    for(int i=0; i<size; i++)
    {
        if(board->content[i]=='B')
        {
            if(board->state[i]!='f')
            {
                board->game=2;
                return;
            }
        }
    }

    board->game=0;
}

void board_lose_out(board_t *board)
{
    int x=board->x;
    int y=board->y;

    printf("     ");

    for(int i=0; i<y; i++)
    {
        if(i+1<10)
        {
            printf(" ");
        }

        printf("%d ", i+1);
    }

    printf("  y\n\n");

    for(int i=0; i<x; i++)
    {
        if(i+1<10)
        {
            printf(" ");
        }

        printf("%d   ", i+1);

        for(int j=0; j<y; j++)
        {
            if(board->state[j+i*y]==' ' && board->bomb_ammount[j+i*y]!=0)
            {
                printf(" %d ", board->bomb_ammount[j+i*y]);
            }
            else
            {
                if(board->content[j+i*y]=='B')
                {
                    printf(" B ");
                }
                else
                {
                    printf(" %c ", board->state[j+i*y]);
                }
            }
        }

        printf("\n");
    }

    printf("\n x\n");
}