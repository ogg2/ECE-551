#include <stdlib.h>
#include <stdio.h>
#include "rand_story.h"

/**
* main for story-step2
*/
int main (int argc, char ** argv) {
  if (argc != 2) {
    fprintf (stderr, "Error: Usage: ./executable inputfile\n");
    return EXIT_FAILURE;
  }

  FILE * file = readFile (argv[1]);
  catarray_t * categories = readWords (file);

  printWords (categories);
  freeCategories (categories);

  closeFile (file);
  return EXIT_SUCCESS;
}
