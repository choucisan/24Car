#ifndef __Encoder_H_
#define __Encoder_H_

#include "A_include.h"


extern int16_t Encoder_Count;
void Encoder_Init(void);
int16_t Encoder_Get(void);
int16_t Encoder1_Get(void);
extern int16_t Encoder_Count,Encoder1_Count,sp1,sp2,length;

#endif

