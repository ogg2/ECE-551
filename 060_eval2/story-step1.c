#include <stdlib.h>
#include <stdio.h>
#include "rand_story.h"

int main (int argc, char ** argv) {
  if (argc != 2) {
    fprintf (stderr, "Error: Usage: ./executable inputfile\n");
    return EXIT_FAILURE;
  }

  FILE * file = readFile (argv[1]);

  /*category_t category;
  category.name = "place";
  char * myWord [2] = {"cave", "lagoon"};
  category.words = myWord;
  category.n_words = 2;

  category_t array[1] = {category};

  catarray_t * categories;
  categories->arr = array;
  categories->n = 1;*/
  readStory (file, NULL);

  //free (categories);

  closeFile (file);
  return EXIT_SUCCESS;
}
