#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "rand_story.h"

/**
* main for story-step4
*/
int main (int argc, char ** argv) {
  if (argc != 3 && argc != 4) {
    fprintf (stderr, "Error: Usage: ./executable -n[optional] inputWords inputStory\n");
    return EXIT_FAILURE;
  }

  int optionalArg = 0;
  if (argc == 4) {
    if (strcmp(argv[1], "-n")) {
      fprintf (stderr, "Error: Optional argument must be \"-n\".\n");
      return EXIT_FAILURE;
    }
    optionalArg = 1;
  }

  FILE * fileWords = readFile (argv[1 + optionalArg]);
  catarray_t * categories = readWords (fileWords);
  closeFile (fileWords);

  FILE * fileStory = readFile (argv[2 + optionalArg]);
  int reuseWords = !optionalArg;
  readStory (fileStory, categories, reuseWords);
  freeCategories (categories);

  closeFile (fileStory);
  return EXIT_SUCCESS;
}
