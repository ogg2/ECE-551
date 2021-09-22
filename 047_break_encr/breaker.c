#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int breaker (int * freq) {
  int freqCount = freq[0];
  int keyCode = 0;
  for (int i = 1; i < 26; i++) {
    if (freq[i] > freqCount) {
      freqCount = freq[i];
      keyCode = i;
    }
  }
  keyCode = keyCode + 'a' - 'e';
  keyCode += 26;
  keyCode %= 26;

  return keyCode;
}

void frequency (FILE * file, int * freq) {
  int c;
  while ((c = fgetc(file)) != EOF) {
    if (isalpha(c)){
      c = tolower (c);
      c -= 'a';
      //int count = freq[c];
      //freq[c] = count++;
      freq[c]++;
    }
  }
}

int main (int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: inputFileName\n");
    EXIT_FAILURE;
  }

  FILE * file = fopen (argv[1], "r");
  if (file == NULL) {
    perror ("Could not open file");
    return EXIT_FAILURE;
  }
  int freq[26] = {0};
  frequency(file, freq);
  
  int codeKey = breaker (freq);
  
  if (fclose(file) != 0) {
    perror ("Failed to close the input file!");
    return EXIT_FAILURE;
  }

  printf("%d\n", codeKey);
  return EXIT_SUCCESS;
}
