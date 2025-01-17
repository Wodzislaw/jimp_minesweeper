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
            getc(stdin);
        }
    }
    
    //printf("poprawne %c\n", temp);

    int x, y, bombs, mult, field;

    if(temp=='e')
    {
        x=9, y=9, bombs=10, mult=1;
        field=x*y;
    }
    else if(temp=='m')
    {
        x=16, y=16, bombs=40, mult=2;
        field=x*y;
    }
    else if(temp=='h')
    {
        x=16, y=30, bombs=99, mult=3;
        field=x*y;
    }
    else
    {
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

        bombs=field*0.2;
    }


    /*
    printf("x = %d\n", x);
    printf("y = %d\n", y);
    printf("t = %d\n", time);
    printf("f = %d\n", field);
    printf("m = %d\n", mult);
    */

    board->x=x;
    board->y=y;
    board->bombs=bombs;
    board->mult=mult;
    board->content=malloc(x * y * sizeof(char));
    board->state=malloc(x * y * sizeof(char));
    board->bomb_ammount=malloc(x * y * sizeof(int));
    board->game=2;
    board->actual_first=1;
    board->points=0;

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
    int bombs=board->bombs;

    srand(time(NULL));
    int random;

    for(int i=0; i<board->x*board->y; i++)
    {
        random=rand() % field + 1;

        if(random<=bombs && i!=board->first_position)
        {
            bombs--;
            board->content[i]='B';
        }
        else
        {
            board->content[i]='N';
        }

        field--;
    }
}


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

    printf("Punkty: %d\n\n", board->points);


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

    if(board->actual_first==1)
    {
        board->first_position=pos;
    }

    if(function=='f')
    {
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
        if(board->state[pos]==' ')
        {
            return;
        }

        if(board->content[pos]=='B')
        {
            board->game=1;
        }
        else
        {
            board->state[pos]=' ';

            board->points+=board->mult;

            if(board->actual_first!=1)
            {
                if(board->bomb_ammount[pos]==0)
                {
                    board_shatter(board);
                }
            }
        }
    }
}

void board_shatter(board_t *board)
{
    int pos=board->current_x * board->y + board->current_y;
    int current_pos;

    bool up=true, left=true, right=true, down=true;
    bool end=false;
    bool up_left=false, up_right=false, down_left=false, down_right=false;

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

                if(left==true && up==true)
                {
                    up_left=true;
                }

                if(right==true && up==true)
                {
                    up_right=true;
                }

                if(left==true && down==true)
                {
                    down_left=true;
                }

                if(right==true && down==true)
                {
                    down_right=true;
                }

                if(left==true)
                {
                    if(board->bomb_ammount[current_pos-1]==0 && board->state[current_pos-1]=='#')
                    {
                        board->state[current_pos-1]=' ';

                        board->current_x=i;
                        board->current_y=j-1;

                        board->points+=board->mult;

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

                        board->points+=board->mult;

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

                        board->points+=board->mult;

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

                        board->points+=board->mult;

                        board_shatter(board);
                    }
                }


                if(up_left==true)
                {
                    if(board->bomb_ammount[current_pos - board->y-1]==0 && board->state[current_pos - board->y-1]=='#')
                    {
                        board->state[current_pos-board->y-1]=' ';

                        board->current_x=i-1;
                        board->current_y=j-1;

                        board->points+=board->mult;

                        board_shatter(board);
                    }
                }

                if(up_right==true)
                {
                    if(board->bomb_ammount[current_pos - board->y+1]==0 && board->state[current_pos - board->y+1]=='#')
                    {
                        board->state[current_pos-board->y+1]=' ';

                        board->current_x=i-1;
                        board->current_y=j+1;

                        board->points+=board->mult;

                        board_shatter(board);
                    }
                }

                if(down_left==true)
                {
                    if(board->bomb_ammount[current_pos + board->y-1]==0 && board->state[current_pos + board->y-1]=='#')
                    {
                        board->state[current_pos+board->y-1]=' ';

                        board->current_x=i+1;
                        board->current_y=j-1;

                        board->points+=board->mult;

                        board_shatter(board);
                    }
                }

                if(down_right==true)
                {
                    if(board->bomb_ammount[current_pos + board->y+1]==0 && board->state[current_pos + board->y+1]=='#')
                    {
                        board->state[current_pos+board->y+1]=' ';

                        board->current_x=i+1;
                        board->current_y=j+1;

                        board->points+=board->mult;

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


    if(left==true && board->state[current_pos-1]!=' ')
    {
        board->state[current_pos-1]=' ';
        board->points+=board->mult;
    }

    if(right==true && board->state[current_pos+1]!=' ')
    {
        board->state[current_pos+1]=' ';
        board->points+=board->mult;
    }

    if(up==true && board->state[current_pos-board->y]!=' ')
    {
        board->state[current_pos-board->y]=' ';
        board->points+=board->mult;
    }

    if(down==true && board->state[current_pos+board->y]!=' ')
    {
        board->state[current_pos+board->y]=' ';
        board->points+=board->mult;
    }


    if(up_left==true && board->state[current_pos-board->y-1]!=' ')
    {
        board->state[current_pos-board->y-1]=' ';
        board->points+=board->mult;
    }

    if(up_right==true && board->state[current_pos-board->y+1]!=' ')
    {
        board->state[current_pos-board->y+1]=' ';
        board->points+=board->mult;
    }

    if(down_left==true && board->state[current_pos+board->y-1]!=' ')
    {
        board->state[current_pos+board->y-1]=' ';
        board->points+=board->mult;
    }

    if(down_right==true && board->state[current_pos+board->y+1]!=' ')
    {
        board->state[current_pos+board->y+1]=' ';
        board->points+=board->mult;
    }

}

void board_check_win(board_t *board)
{
    int x=board->x;
    int y=board->y;
    int size=x*y;

    for(int i=0; i<size; i++)
    {
        if(board->content[i]=='N')
        {
            if(board->state[i]!=' ')
            {
                board->game=2;
                return;
            }
        }
    }

    board->game=0;
}

void board_end_out(board_t *board)
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