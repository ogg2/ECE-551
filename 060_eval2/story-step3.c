#include <stdlib.h>
#include <stdio.h>
#include "rand_story.h"

int main (int argc, char ** argv) {
  if (argc != 3) {
    fprintf (stderr, "Error: Usage: ./executable inputWords inputStory\n");
    return EXIT_FAILURE;
  }

  FILE * fileWords = readFile (argv[1]);
  catarray_t * categories = readWords (fileWords);
  closeFile (fileWords);

  FILE * fileStory = readFile (argv[2]);
  readStory (fileStory, categories, 0);
  freeCategories (categories);

  closeFile (fileStory);
  return EXIT_SUCCESS;
}
