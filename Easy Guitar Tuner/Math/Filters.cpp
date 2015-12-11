//
//  Filters.cpp
//  VoiceRecordPlayObjectiveC
//
//  Created by Apple on 20/10/15.
//  Copyright (c) 2015 B. Lake. All rights reserved.
//

#include "Filters.h"
#include "math.h"

const float PI = 3.14159265359f;
const float TWOPI = 6.2831853f;

void filterSignal(float* input, float *output, float* filter, int signalsize, int filtersize){
    
    int temp = (filtersize - 1) / 2;
    float temp2 = 0;
    for (int i = temp; i < signalsize - temp; i++){
        temp2 = 0;
        for (int j = (-1*temp); j<=temp; j++){
            temp2 += (input[i + j] * filter[temp + j]);
        }
        output[i] = temp2;
    }
    
}

void createLowpassBlackman(int M, float* filter)
{
    float sum = 0;
    for (int i = 0; i < M; i++)
    {
        filter[i] = 0.42f - 0.5f * cosf(i * TWOPI / (float)M) + 0.08f * cosf(4.0f * PI * (float)i / (float)(M));
        sum += filter[i];
    }
    for (int i = 0; i < M; i++)
    {
        filter[i] = filter[i] / sum;
    }
}

void downSample(float* input, float *output, int length, int m)
{
    for (int i = 0; i < length/m; i++)
    {
        output[i] = input[m * i];
    }
}

