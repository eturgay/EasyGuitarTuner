//
//  SignalGenerater.cpp
//  SoundAnalyser
//
//  Created by Apple on 04/11/15.
//  Copyright © 2015 B. Lake. All rights reserved.
//

#include "SignalGenerator.hpp"
#include "SignalDefinitions.h"
#include <math.h>
#include <random>
#include "../Globals/GlobalVariables.hpp"

const float PI = 3.14159265359;

void GenerateSignals(float f1, float f2, float std)
{
    float dt = 1.0f / (float)samplingRate;
    for (int i = 0; i < SIGNAL_LENGTH; i++) {
        testSignalNoise[i] = float(rand() % 100000 - 50000)/50000.0f * std;
        testSignalDoubleSinus[i] = 0.2f * cosf(2 * PI * f1 * i * dt) + 0.2f * cosf(2 * PI * f2 * i * dt);
        testSignalDoubleSinusInNoise[i] = testSignalDoubleSinus[i] + testSignalNoise[i];
        testSignalString[i] = 0.2f * cosf(2 * PI * f1 * i * dt) + 0.3f * cosf(2 * PI * 2 * f1 * i * dt + 0.1)
                         + 0.05f * cosf(2 * PI * 3 * f1 * i * dt + 0.2) + 0.1f * cosf(2 * PI * 4 * f1 * i * dt + 0.3)
                         + 0.2f * cosf(2 * PI * 5 * f1 * i * dt + 0.4);
    }
    
    for (int i = 5; i < SIGNAL_LENGTH; i++) {
        testSignalARMA[i] = testSignalNoise[i] - (0.6 * testSignalARMA[i-2] + 0.4 * testSignalARMA[i-4] + 0.5 * testSignalARMA[i-5]);
    }
    
}