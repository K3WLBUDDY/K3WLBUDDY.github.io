#include <stdio.h>
#include <stdlib.h>
#include <time.h>


float computeLoss(float *LHS, float *RHS, float weight)
{
    float loss = 0;
    float *temp = calloc(5, sizeof(float));

    for(int i = 0; i < 5; i++)
    {
        temp[i] = RHS[i] * weight;
        loss += (abs(temp[i] - LHS[i]));
    }

    return loss; 
}

int main(int argc, char **argv)
{
    float *LHS = calloc(5, sizeof(float));
    float *RHS = calloc(5, sizeof(float));
    srand (time(0));
    float weight = (float)rand()/(float)(RAND_MAX/1000.0);
    float bestWeight;
    //float weight = rand() % 100 + 1;

    LHS[0] = 35000;
    LHS[1] = 14000;
    LHS[2] = 25000;
    LHS[3] = 38000;
    LHS[4] = 10000;

    RHS[0] = 1200;
    RHS[1] = 600;
    RHS[2] = 1000;
    RHS[3] = 1500;
    RHS[4] = 435;

    float loss = computeLoss(LHS, RHS, weight);
    float newLoss;
    
    for(int i = 0; i < 100000; i++)
    {
        //weight = rand() % 100 + 1;
        weight = (float)rand()/(float)(RAND_MAX/1000.0);
        newLoss = computeLoss(LHS, RHS, weight);
        //printf("\n New loss after %d iterations : %f", i, newLoss);
        if(newLoss < loss)
        {    
            loss = newLoss;
            bestWeight = weight;
        }
        printf("\n Loss after %d iterations : %f", i, loss);
        /*
        if(loss <= 7375.0)
        {
            printf("\n WTF");
            printf("\n WEight : %d", weight);
            return(0);
        }
        */
    }

    printf("\n Final Weights : %f", bestWeight);

    
}