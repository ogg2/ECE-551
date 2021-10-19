#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "rand_story.h"

int main (int argc, char ** argv) {
  if (argc != 3 && argc != 4) {
    fprintf (stderr, "Error: Usage: ./executable -n[optional] inputWords inputStory\n");
    return EXIT_FAILURE;
  }

  int optional = 0;
  if (argc == 4) {
    if (strcmp(argv[1], "-n")) {
      fprintf (stderr, "Error: Optional argument must be a \"-n\".\n");
      return EXIT_FAILURE;
    }
    optional = 1;
  }

  FILE * fileWords = readFile (argv[1 + optional]);
  catarray_t * categories = readWords (fileWords);
  closeFile (fileWords);

  FILE * fileStory = readFile (argv[2 + optional]);
  int reuseWords = !optional;
  readStory (fileStory, categories, reuseWords);
  freeCategories (categories);

  closeFile (fileStory);
  return EXIT_SUCCESS;
}
