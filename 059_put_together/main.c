#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

void closeFile (FILE * file) {
  if (fclose (file) != 0) {
    fprintf (stderr, "Error: Failed to close file.\n");
    exit (EXIT_FAILURE);
  }
}

FILE * openFileWR (const char * fname, char * operation) {
  FILE * file = fopen (fname, operation);
  if (file == NULL) {
    fprintf (stderr, "Error: Could not open file.\n");
    exit (EXIT_FAILURE);
  }
  return file;
}

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE * file = openFileWR (filename, "r");

  counts_t * counts = createCounts();
  char * key = NULL;
  size_t size;
  while (getline (&key, &size, file) >= 0) {
    char * keys = NULL;
    keys = readString (keys, key, '\n');

    //char * end = strchr (key, '\n');
    //char * keys = strndup (key, (size_t) (end - key));
    
    char * value = lookupValue (kvPairs, keys);
    addCount (counts, value);
    free (key);
    free (keys);
    key = NULL;
  }
  free (key);

  closeFile (file);
  return counts;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc <= 2) {
    fprintf (stderr, "Usage: ./count_values [inputfile pairs] [inputfile lists]");
    return EXIT_FAILURE;
  }
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kvPairs = readKVs (argv[1]);

  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile (argv[i], kvPairs);
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName (argv[i]);
    //open file name outName
    FILE * f = openFileWR (outName, "w");
    //print counts from c into FILE f
    printCounts (c, f);
    //close f
    closeFile (f);
    //free the memory for outName and c
    free (outName);
    freeCounts (c);
  }

  //free the memory for kv
  freeKVs (kvPairs);

  return EXIT_SUCCESS;
}
