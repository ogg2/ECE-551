#include <stdlib.h>
#include <stdio.h>
#include "rand_story.h"

int main (int argc, char ** argv) {
  if (argc != 2) {
    fprintf (stderr, "Error: Usage: ./executable inputfile\n");
    return EXIT_FAILURE;
  }

  FILE * file = readFile (argv[1]);
  catarray_t * array = readWords (file);
  printWords (array);

  closeFile (file);
  return EXIT_SUCCESS;
}
