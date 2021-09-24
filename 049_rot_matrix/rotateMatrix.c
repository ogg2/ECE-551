#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rotate (const char ** matrix) {

  for (int col = 0; col < 10; col++) {
    for (int row = 9; row >= 0; row--) {
      char character;
      if ((character = matrix[row][col]) == '\0' || character == EOF) {
        fprintf(stderr,"Input file not formatted correctly. Too few characters.\n");
        exit (EXIT_FAILURE);
      }
      printf ("%c", character);
    }
      printf ("\n");
  }
}

int main (int argc, char ** argv) {
  if (argc != 2) {
    fprintf (stderr, "Incorrect number of input parameters.\n");
    return EXIT_FAILURE;
  }

  FILE * file = fopen (argv[1], "r");
  if (file == NULL) {
    fprintf (stderr, "Could not open file.\n");
    return EXIT_FAILURE;
  }

  //const char * matrix [12] = {word0, word1, word2, word3, word4, word5, word6, word7, word8, word9};
  const char * matrix[12];
  int i = 0;
  char word[12];

  //WHY DOESNT THIS WORK
  while (fgets(word, 12, file) != NULL) {
    if (strchr(word, '\n') == NULL) {
      fprintf(stderr, "Input file is not formatted correctly. Line is too long.\n");
      return EXIT_FAILURE;
    }
    /*if (word[10] == '\0') {
      fprintf(stderr, "Input file is not formatted correctly. Line is too short.\n");
      return EXIT_FAILURE;
    }*/
    if (i > 9) {
      fprintf(stderr, "Input file is not formatted correctly. Too many lines.\n");
      return EXIT_FAILURE;
    }
    matrix[i++] = strdup(word);
  }
  if (i < 9) {
    fprintf(stderr, "Input file is not formatted correctly. Too few lines.\n");
    return EXIT_FAILURE;
  }
  
  rotate (matrix);

  if (fclose (file) != 0) {
    fprintf (stderr, "Failed to close the input file.\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
