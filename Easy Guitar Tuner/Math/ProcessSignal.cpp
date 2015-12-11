 //
//  ProcessSignal.cpp
//  VoiceRecordPlayObjectiveC
//
//  Created by Apple on 21/10/15.
//  Copyright (c) 2015 B. Lake. All rights reserved.
//

#include "ProcessSignal.h"
#include "FftImplementations.hpp"
#include "Filters.h"
#include "SignalModelling.hpp"
#include "SignalGenerator.hpp"
#include "../Globals/GlobalVariables.hpp"

float F1[] = {0.05, 0.1, 0.2, 0.3, 0.2, 0.1, 0.05};

void GenerateTestSignals()
{
    GenerateSignals(440, 440, 0.5);
    for (int i = 0; i < SIGNAL_LENGTH; i++) {
        //signal1[i]  = testSignalNoise[i];
        //signal1[i]  = testSignalDoubleSinus[i];
        signal1[i]  = testSignalString[i];
        // signal1[i]  = testSignalARMA[i];
    }
    
}

void PrepareGraph1ForPlot(){
    for (int i = 0; i < SIGNAL_LENGTH; i++){
        if (signal1[i] > -1.0f)
            Graph1Data[i] = signal1[i] * 20 + 20;
        else
            Graph1Data[i] = 0;
    }
    //
}
void PrepareGraph2ForPlot(int toggleGraph){
    if (toggleGraph == 0)
    {
        for (int i = 0; i < (dftLength/2); i++){
                Graph2Data[i] = 2*signal1FA[i];
        }
        toggleGraph = 1;
    }
    else if (toggleGraph == 1)
    {
        for (int i = 0; i < (dftLength); i++){
            if (signal1[i] > -1.0f)
                Graph2Data[i] = signal1[i] * 20 + 20;
            else
                Graph2Data[i] = 0;
        }
        toggleGraph = 2;
    }
    else if (toggleGraph == 2)
    {
        for (int i = 0; i < (dftLength); i++){
            if (signal2[i] > -1.0f)
                Graph2Data[i] = signal2[i] * 20 + 20;
            else
                Graph2Data[i] = 0;
        }
        toggleGraph = 3;
    }
    else if (toggleGraph == 3)
    {
        for (int i = 0; i < (dftLength); i++){
            if (signal3[i] > -1.0f)
                Graph2Data[i] = signal3[i] * 20 + 20;
            else
                Graph2Data[i] = 0;
        }
        toggleGraph = 0;
    }
}

float sAc[]  = {1, 2, 3, 2, 1, 2, 3, 4, 3, 2, 1, 2 ,3 ,4, 3, 2, 1, 2, 3, 4, 3, 2, 1, 2, 3, 2 ,1 ,2};

void Process1(){
    //filterSignal(signal1, signal2, F1, SIGNAL_LENGTH, 7);
    PrepareGraph1ForPlot();}

void Process2(int toggleGraph)
{
    float filter1[100];
    createLowpassBlackman(lpFilterLength, filter1);
    filterSignal(signal1, signal2, filter1, SIGNAL_LENGTH, lpFilterLength);
    downSample(signal2, signal3, SIGNAL_LENGTH, downSamplingFactor);

    int autocorrDepth = samplingRate / downSamplingFactor / 84 + 20;
    if (autocorrDepth > 500) autocorrDepth = 499;
    EstimateAutoCorrelationValues(signal3, autoCorr, dftLength, autocorrDepth);
    int offset = samplingRate / downSamplingFactor / 2 / 440;
    int secondPeak=offset;
    findSecondPeak(autoCorr, &secondPeak, autocorrDepth, offset);
    firstHarmonic = samplingRate / downSamplingFactor / secondPeak;
}



float f1[] = {0.3, 0.4, 0.3};
float s1[] = {0.1, 0.5, 0.1, 0.5, 0.1, 0.5, 0.1, 0.5};
float s2[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float s3[] = {1.0, 2.0, 3.0, 4.0};
float s3FR[] = {0.0, 0.0, 0.0, 0.0};
float s3FI[] = {0.0, 0.0, 0.0, 0.0};


float rVal[]  = {8, 5, 4, 3, 2, 1, 0, 0, 0, 0};
float ap[]    = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
float error[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
float c[]     = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
float A[10][10];

//
void TestREstimate()
{
    
    EstimateARMASpectrum(sAc, autoCorr, aCoeff, spectrumEstimate, 28, 3, errorHistory);
    
    EstimateAutoCorrelationValues(sAc, rVal, 4, 3);
    A[0][0] =  1;A[0][1] = -1;A[0][2] =  2;A[0][3] = -1;A[0][4] = 3;
    A[1][0] =  1;A[1][1] =  1;A[1][2] =  1;A[1][3] =  1;A[1][4] = 1;
    A[2][0] = -1;A[2][1] =  2;A[2][2] =  4;A[2][3] = -1;A[2][4] = 0;
    A[3][0] =  0;A[3][1] =  2;A[3][2] =  0;A[3][3] =  1;A[3][4] = 2;
    A[4][0] =  3;A[4][1] =  4;A[4][2] =  1;A[4][3] =  0;A[4][4] = 2;
    c[0] = 16;
    c[1] = 15;
    c[2] = 11;
    c[3] = 18;
    c[4] = 24;
    float TotalError = RLS(A, c, ap, 5);
}

void swap(int* data, int i, int j)
{
    int tmp = data[i];
    data[i] = data[j];
    data[j] = tmp;
}

void BubbleSort(int* data, int length)
{
    
    for (int i = 0; i < length; ++i)
    {
        bool swapped = false;
        for (int j = 0; j < length - (i+1); ++j)
        {
            if (data[j] > data[j+1])
            {
                swap(data, j, j+1);
                swapped = true;
            }
        }
        
        if (!swapped) break;
    }
}

void findPeaks(float* input, int* list, int length, int m, int w)
{
    float max = 0;
    int index = 0;
    int index2 = 0;
    for (int k = 0; k < m; k++){
        index = 0;
        max = 0;
        for (int i = 0; i <length; i++) {
            if (input[i] > max) {
                max = input[i];
                index = i;
            }
        }
        list[k] = index;
        
        for (int m = (-1*w); m <= w; m++) {
            index2 = m + index;
            if (index2 > 0 && index2 < length)
                input[index2] = 0;
        }
    }
    
    BubbleSort(list, m);
}
void findSecondPeak(float* input, int* peak, int length, int offset)
{
    float max = 0;
    *peak = offset;
    for (int i = offset; i < length; i++) {
        if (input[i] > max) {
            max = input[i];
            *peak = i;
        }
    }
}

int toggleme = 0;
    
void TestCase1(){
    GenerateTestSignals();
    DFT(s3, s3FR, s3FI, 4);
    float filter1[100];
    createLowpassBlackman(lpFilterLength, filter1);
    filterSignal(signal1, signal2, filter1, SIGNAL_LENGTH, lpFilterLength);
    downSample(signal2, signal3, SIGNAL_LENGTH, downSamplingFactor);
    DFT(signal3, signal1FR, signal1FI, dftLength);
    ABS(signal1FR, signal1FI, signal1FA, dftLength);
    //
    if (toggleme == 0)
    {
        
        for (int i = 0; i < SIGNAL_LENGTH; i++){
            if (signal1[i] > -10.0f)
                Graph1Data[i] = signal1[i] * 2 + 20;
            else
                Graph1Data[i] = 0;
        }

        toggleme = 1;
    }
    else if (toggleme == 1)
    {
        
        for (int i = 0; i < SIGNAL_LENGTH; i++){
            if (signal2[i] > -10.0f)
                Graph1Data[i] = signal2[i] * 2 + 20;
            else
                Graph1Data[i] = 0;
        }

        toggleme = 2;
    }
    else if (toggleme == 2)
    {
        
        for (int i = 0; i < SIGNAL_LENGTH; i++){
            if (signal3[i] > -10.0f)
                Graph1Data[i] = signal3[i] * 2 + 20;
            else
                Graph1Data[i] = 0;
        }
        
        toggleme = 3;
    }
    else if (toggleme == 3)
    {
        for (int i = 0; i < (SIGNAL_FFT_LENGTH/2); i++){
            Graph1Data[i] = 0.001*signal1FA[i];
        }
        toggleme = 0;
    }
    
    int window  = 10;
    findPeaks(signal1FA, peaklist, dftLength/2, 2, window);
    
    EstimateAutoCorrelationValues(signal1, autoCorr, dftLength, 300);
    int offset = samplingRate / downSamplingFactor / 2 * 440;
    int secondPeak;
    findSecondPeak(signal1FA, &secondPeak, dftLength/2, offset);
    firstHarmonic = samplingRate / downSamplingFactor / secondPeak;
    
}
void TestView2(){
    GenerateTestSignals();
}









