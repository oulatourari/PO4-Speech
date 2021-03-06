#pragma once
#include "globals.h"
#include "receiver.h"
struct encoderChunk {
	short prevBufferEven[25];
	short prevBufferOdd[25];
	short prevBufferC0Even[12];
	short prevBufferC0Odd[12];
	short prevBufferC1Even[12];
	short prevBufferC1Odd[12];
	short prediction1;
	short prediction2;
	short prediction3;
	short prediction4;
	short stepsize1;
	short stepsize2;
	short stepsize3;
	short stepsize4;
	short deltaPrimeArray1[nbDelta];
	short deltaPrimeArray2[nbDelta];
	short deltaPrimeArray3[nbDelta];
	short deltaPrimeArray4[nbDelta];
};

void transmitter(short *buffer, struct encoderChunk * encoderLeftChunk, struct encoderChunk *encoderRightChunk, unsigned short encodedBuffer[8]);
void analysis(short buffer[BUFFERSIZE], short subband1[BUFFERSIZE/8],  short subband2[BUFFERSIZE/8],  short subband3[BUFFERSIZE/8],  short subband4[BUFFERSIZE/8], struct encoderChunk * encoderChunk);
void ConvolutionStage1(short inputEven[25], short inputOdd[25], long long  C0[BUFFERSIZE/4], long long C1[BUFFERSIZE/4]);
void ConvolutionStage2(short C0Even[7], short C0Odd[7], short C1Even[7], short C1Odd[7], short subband1[BUFFERSIZE/8],  short subband2[BUFFERSIZE/8],  short subband3[BUFFERSIZE/8],  short subband4[BUFFERSIZE/8]);

void ADPCMencoder(short *subband1, short *subband2, short *subband3, short *subband4, struct encoderChunk * encoderChunk);
void ADPCMencoderSubband(short *subbandSignal, short mu,
	short *prediction, short* codebook, short codebookSize, short *stepsize,
	short *deltaPrimeArray, short phi_updated);
short quantize(int value, short* codebook, short codebookSize, short stepsize);
short calculateStepsize(short* deltaPrimeArray, short phi_updated);
long long calculateStd(short* deltaPrimeArray);
short calculateStdFP(short* deltaPrimeArray);

unsigned short shiftAndCast2(short value, short nbBits);
unsigned short shiftAndCast4(short value, short nbBits);

unsigned long long calculateSqrt(unsigned long long value);
