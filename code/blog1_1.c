#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "csvRead.h"

float computeLoss(csv *c, float weight)
{
    long double loss = 0;
    float *temp = calloc(c->rows, sizeof(float));

    for(int i = 0; i < c->rows; i++)
    {
        temp[i] = c->vals[i][0] * weight;
        loss += (abs(temp[i] - c->vals[i][1]));
    }

    free(temp);
    return (loss/c->rows); 
}

float computeSquaredLoss(csv *c, float weight)
{
    long double loss = 0;
    float *temp = calloc(c->rows, sizeof(float));

    for(int i = 0; i < c->rows; i++)
    {
        temp[i] = c->vals[i][0] * weight;
        loss += pow(abs(temp[i] - c->vals[i][1]), 2);
    }
    free(temp);

    return (pow(loss, 0.5)/c->rows);
}

int main(int argc, char **argv)
{

    if(argc < 2)
    {
        printf("\n Usage : ./test <PATH TO CSV FILE>");
        return(-1);
    }

    csv c = csvRead(argv[1]);
    
    srand (time(NULL));
    float weight = (float)rand()/(float)(RAND_MAX/100.0);
    float bestWeight;
    float bestWeight2;
    float loss = computeLoss(&c, weight);
    float lossSq = computeSquaredLoss(&c, weight);
    
    float newLoss;
    float newLossSq;
    
    for(int i = 0; i < 10000; i++)
    {
        weight = (float)rand()/(float)(RAND_MAX/100.0);
        newLoss = computeLoss(&c, weight);
        if(newLoss < loss)
        {    
            loss = newLoss;
            bestWeight = weight;
        }

        weight = (float)rand()/(float)(RAND_MAX/100.0);
        newLossSq = computeSquaredLoss(&c, weight);
        
        if(newLossSq < lossSq)
        {    
            lossSq = newLossSq;
            bestWeight2 = weight;
        }
        printf("\n Loss after %i iteartions : %f \t Loss after %i iteartions : %f", i, loss,i,lossSq);
    }

    printf("\n Best Loss : %f \t Best Loss Sq : %f", loss, lossSq);
    printf("\n Best Weight : %f \t Best Weight Sq : %f",bestWeight, bestWeight2);

    weight = 29.16;
    loss = computeSquaredLoss(&c, weight);

    printf("\n NEW LOSS : %f", loss);
    
    
}