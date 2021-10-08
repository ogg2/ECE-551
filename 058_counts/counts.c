#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
  //WRITE ME
  /*one_count_t one;
  one.string = NULL;
  one.count = 0;*/
  
  counts_t * counts = malloc (sizeof(*counts));
  counts->counts = NULL;
  counts->size = 0;
  counts->unknowns = 0;
  return counts;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->unknowns = c->unknowns + 1;
    return;
  }
  size_t size = c->size;
  one_count_t * array = c->counts;
  for (size_t i = 0; i < size; i++) {
    if (!strcmp (array[i].string, name)) {
      array[i].count = array[i].count + 1;
      return;
    }
  }
  one_count_t one;
  one.string = name;
  one.count = 1;
  array = realloc (array, (size + 1) * sizeof(*array));
  array[size] = one;
  c->counts = array;
  c->size = c->size + 1;
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME

  size_t size = c->size;
  one_count_t * array = c->counts;
  for (size_t i = 0; i < size; i++) {
    fprintf (outFile, "%s: ", array[i].string);
    fprintf (outFile, "%zu\n", array[i].count);
  }
  size_t unknowns = c->unknowns;
  if (unknowns != 0) {
    fprintf (outFile, "<unknown> : %zu\n", unknowns);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  free (c->counts);
  free (c);
}
