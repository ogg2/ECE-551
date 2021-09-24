#include <stdio.h>
#include <stdlib.h>

void rotate (const char ** matrix) {

  for (int col = 0; col < 10; col++) {
    for (int row = 9; row >= 0; row--) {
      printf ("%c", matrix[row][col]);
    }
      printf ("\n");
  }
}

int main (int argc, char ** argv) {
  if (argc != 2) {
    fprintf (stderr, "Incorrect nubmer of input parameters.\n");
    return EXIT_FAILURE;
  }

  FILE * file = fopen (argv[1], "r");
  if (file == NULL) {
    fprintf (stderr, "Could not open file.\n");
    return EXIT_FAILURE;
  }

  char word0[12];
  fgets(word0, 12, file);
  char word1[12];
  fgets(word1, 12, file);
  char word2[12];
  fgets(word2, 12, file);
  char word3[12];
  fgets(word3, 12, file);
  char word4[12];
  fgets(word4, 12, file);
  char word5[12];
  fgets(word5, 12, file);
  char word6[12];
  fgets(word6, 12, file);
  char word7[12];
  fgets(word7, 12, file);
  char word8[12];
  fgets(word8, 12, file);
  char word9[12];
  fgets(word9, 12, file);

  const char * matrix [12] = {word0, word1, word2, word3, word4, word5, word6, word7, word8, word9};

  //WHY DOESNT THIS WORK
 /* while (fgets(word, 12, file) != NULL) {
    matrix[i] = word;
    i++;
  }*/
  
  rotate (matrix);

  if (fclose (file) != 0) {
    fprintf (stderr, "Failed to close the input file.\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
