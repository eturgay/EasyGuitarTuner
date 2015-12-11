//
//  ProcessSignal.h
//  VoiceRecordPlayObjectiveC
//
//  Created by Apple on 21/10/15.
//  Copyright (c) 2015 B. Lake. All rights reserved.
//

#ifndef __VoiceRecordPlayObjectiveC__ProcessSignal__
#define __VoiceRecordPlayObjectiveC__ProcessSignal__

#include "SignalDefinitions.h"


#ifdef __cplusplus
extern "C" {
#endif
    

extern void Process1();
extern void Process2(int toggleGraph);
extern void TestCase1();
extern void TestView2();
extern void GenerateTestSignals();
void findPeaks(float* input, int* list, int length, int m, int w);
void findSecondPeak(float* input, int* peak, int length, int offset);
    
#ifdef __cplusplus
}
#endif

#endif /* defined(__VoiceRecordPlayObjectiveC__ProcessSignal__) */
