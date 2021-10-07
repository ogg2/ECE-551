#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  char * outputName;

  outputName = malloc (sizeof(inputName) + sizeof(inputName) * 6);
  char * output = outputName;
  while (*inputName != '\0') {
    *outputName = *inputName;
    inputName++;
    outputName++;
  }
  char * counts = ".counts";
  for (int i = 0; i < 7; i++) {
    *outputName = counts[i];
    outputName++;
  }
  *outputName = '\0';

  return output;
}
