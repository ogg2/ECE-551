#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"


char * readString (char * string, char * line, int c) {
  int character;
  size_t stringSize = 0;
  
  while ((character = *line) != c) {
    string = realloc (string, (1 + stringSize) * sizeof (*string));
    string[stringSize++] = character;
    line++;
  }

  string = realloc (string, (1 + stringSize) * sizeof (*string));
  string[stringSize] = '\0';
  return string;
}

FILE * openFile (const char * fname) {
  FILE * file = fopen (fname, "r");
  if (file == NULL) {
    fprintf (stderr, "Error: Could not open file.\n");
    exit (EXIT_FAILURE);
  }
  return file;
}

void fileClose (FILE * file) {
  if (fclose(file) != 0) {
    fprintf(stderr, "Error: Failed to close the input file!\n");
    exit (EXIT_FAILURE);
  }
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * file = openFile (fname);

  char * line = NULL;
  size_t size;
  kvpair_t * pairs_array = NULL;
  size_t numPairs = 0;
  while (getline (&line, &size, file) >= 0) {
    pairs_array = realloc (pairs_array, (numPairs + 1) * sizeof (*pairs_array));

    char * key = NULL;
    key = readString(key, line, '=');

    char * value = NULL;
    char * endValue = strchr(line, '=');
    value = readString(value, ++endValue, '\n');

    kvpair_t * pair = malloc (sizeof(*pair));
    pair->key = key;
    pair->value = value;

    pairs_array[numPairs++] = *pair;
    free (pair);
  }
  free (line);

  kvarray_t * pairs = malloc (sizeof(*pairs));
  pairs->pairs = pairs_array;
  pairs->size = numPairs;

  fileClose (file);
  return pairs;
}


void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  size_t size = pairs->size;
  kvpair_t * array = pairs->pairs;

  for (size_t i = 0; i < size; i++) {
    free (array[i].key);
    free (array[i].value);
  }
  free (array);
  free (pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  size_t size = pairs->size;
  kvpair_t * array = pairs->pairs;

  for (size_t i = 0; i < size; i++) {
    printf ("key = '%s' ", array[i].key);
    printf ("value = '%s'\n", array[i].value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  size_t size = pairs->size;
  kvpair_t * array = pairs->pairs;
  for (size_t i = 0; i < size; i++) {
    if (!strcmp (array[i].key, key)) {
      return array[i].value;
    }
  }
  return NULL;
}
