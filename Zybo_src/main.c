﻿#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "wavpcm_io.h"
#include "globals.h"
#include "transmitter.h"
#include "receiver.h"

/* This is the function that is called when the program starts. */
int main (int argc, char *argv[])
{
  clock_t begin = clock();
  /* Variable declarations. */
  struct wavpcm_input input;
  struct wavpcm_output output;
  short buffer[BUFFERSIZE]; 
  short reconstructedBuffer[BUFFERSIZE];
  int bufPos, bufIndex, read;
  unsigned short encodedBuffer[8];


  /* Struct initialization */
  struct encoderChunk encoderChunkLeft;
  memset(&encoderChunkLeft,0,sizeof(struct encoderChunk));
    
  struct encoderChunk encoderChunkRight;
  memset(&encoderChunkRight,0,sizeof(struct encoderChunk));
    
  struct decoderChunk decoderChunkLeft;
  memset(&decoderChunkLeft,0,sizeof(struct decoderChunk));
  decoderChunkLeft.stepsize1 = 1;
  decoderChunkLeft.stepsize2 = 1;
  decoderChunkLeft.stepsize3 = 1;
  decoderChunkLeft.stepsize4 = 1;
    
  struct decoderChunk decoderChunkRight;
  memset(&decoderChunkRight,0,sizeof(struct decoderChunk));
  decoderChunkRight.stepsize1 = 1;
  decoderChunkRight.stepsize2 = 1;
  decoderChunkRight.stepsize3 = 1;
  decoderChunkRight.stepsize4 = 1;
    
  memset(&input, 0, sizeof(struct wavpcm_input));
  input.resource=INPUTWAVFILE;
  memset(&output, 0, sizeof(struct wavpcm_output));
  output.resource=OUTPUTWAVFILE;

    
   
  /* First open input file and parse header, */
  wavpcm_input_open (&input);
  /* and then use this same header configuration for the output file */
  wavpcm_output_copy_settings(&input, &output);
  wavpcm_output_open(&output);
  /*bufPos expressed in temporal samples*/
  for (bufPos=0; bufPos<input.samplesAvailable; bufPos+=(BUFFERSIZE/2)) {
    /* Try to read BUFFERSIZE samples (16 bits, pairwise identical if input is mono, interleaved if input is stereo)  */
    /* into buffer, with read the actual amount read (expressed in bytes! =  (2*read)/(channels * bitDepth/8) array elements)*/
    read = wavpcm_input_read (&input, buffer);
      
      
    /* transform buffer (ENCODER) */
	transmitter(buffer, &encoderChunkLeft, &encoderChunkRight, encodedBuffer);
      
      
    /* if required, dump compressed output */
      
    /* inverse transform buffer (DECODER)*/
	receiver(encodedBuffer, buffer, &decoderChunkLeft, &decoderChunkRight);
      
      for (bufIndex=0; bufIndex<BUFFERSIZE; bufIndex++){
          reconstructedBuffer[bufIndex]=buffer[bufIndex];
      }
      
    /* dump reconstructed output */
    wavpcm_output_write (&output, reconstructedBuffer, read);

  }
    
  /* finalize output (write header) and close */
  wavpcm_output_close (&output);  

  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("time spent: %f \n", time_spent);
  
  /* Return successful exit code. */
  return 0;
}
