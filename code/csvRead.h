#ifndef CSVREAD_H
#define CSVREAD_H

#include <stdlib.h>

typedef struct csv
{
    int rows;
    int cols;
    int nEntries;
    char ***values;
    float **vals;
}csv;

csv c;

static void getDimensions(FILE *fp)
{
    c.rows = 0;
    c.cols = 1;
    int x;
    int flag = 0;
    while((x=fgetc(fp))!= EOF)
    {
        if(flag == 0 && x == ',')
            c.cols++;
        if(x=='\n')
        {
            flag = 1;
            c.rows++;
        }

    }
    c.rows++;

    printf("%d", c.rows);

}

csv csvRead(const char *filePath)
{
    FILE *fp = fopen(filePath, "r");

    if(fp == NULL)
    {    
        perror("CSV Read Error : ");
        exit(-1);
    }

    getDimensions(fp);

    fseek(fp, 0, SEEK_SET);

    c.vals = malloc(c.rows *sizeof(float *));

    for(int i = 0; i < c.rows; i++)
        c.vals[i] = malloc(c.rows * sizeof(float));

    for(int i = 0; i < c.rows; i++)
        fscanf(fp, "%f , %f", &c.vals[i][0], &c.vals[i][1]);

    fclose(fp);

    return c;

}

void csvDelete(csv *c)
{
    for(int i = 0; i < c->rows; i++)
        free(c->vals[i]);
    free(c->vals);
}

#endif