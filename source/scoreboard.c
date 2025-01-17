#include "scoreboard.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 5

void scoreboard_get(scoreboard_t *scoreboard)
{
    char* fname="../data/scrbrd.txt";
    FILE *in = fopen(fname, "r");

    for(int i=0; i<MAX_LINES; i++)
    {
        fscanf(in, "%3s %d", scoreboard->name[i], &scoreboard->points[i]);
    }

    fclose(in);
}

void scoreboard_edit(scoreboard_t *scoreboard, char* name, int points)
{
    int temp=MAX_LINES;

    for(int i=MAX_LINES-1; i>=0; i--)
    {
        if(points>scoreboard->points[i])
        {
            temp=i;
        }
    }

    
    if(temp!=MAX_LINES)
    {
        for(int i=MAX_LINES-1; i>temp; i--)
        {
            scoreboard->name[i][0]=scoreboard->name[i-1][0];
            scoreboard->name[i][1]=scoreboard->name[i-1][1];
            scoreboard->name[i][2]=scoreboard->name[i-1][2];
            scoreboard->points[i]=scoreboard->points[i-1];
        }

        scoreboard->name[temp][0]=name[0];
        scoreboard->name[temp][1]=name[1];
        scoreboard->name[temp][2]=name[2];
        scoreboard->points[temp]=points;
    }


    for(int i=0; i<MAX_LINES; i++)
    {
        printf("%s: %d\n", scoreboard->name[i], scoreboard->points[i]);
    }

    printf("\n");
}

void scoreboard_out(scoreboard_t *scoreboard)
{
    char* fname="../data/scrbrd.txt";
    FILE *out = fopen(fname, "w");

    for(int i=0; i<MAX_LINES; i++)
    {
        fprintf(out, "%3s %d\n", scoreboard->name[i], scoreboard->points[i]);
    }

    fclose(out);
}