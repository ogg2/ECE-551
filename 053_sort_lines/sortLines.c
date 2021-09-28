#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void printArray (char ** data, size_t size) {
  for (size_t i = 0; i < size; i++) {
    printf ("%s", data[i]);
    free (data[i]);
  }
}

char ** addToArray (char ** data, size_t size, char * line) {
  data = realloc (data, (1 + size) * sizeof (*data));
  data[size] = line;
  return data;
}

void readFile (FILE * file) {
  char * line = NULL;
  size_t sz;
  char ** data = NULL;
  size_t numLines = 0;
  while (getline (&line, &sz, file) >= 0) {
    data = addToArray (data, numLines, line);
    numLines++;
    line = NULL;
  }
  free (line);
  sortData (data, numLines);
  printArray (data, numLines);
  free (data);
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  if (argc == 1) {
    char * buffer;
    size_t sz;
    char ** data = NULL;
    size_t numLines = 0;
    do {
      buffer = NULL;
      if (getline (&buffer, &sz, stdin) >= 0) {
        data = addToArray (data, numLines, buffer);
        numLines++;
      }
    } while (*buffer != '\n');

    free (buffer);
    sortData (data, numLines);
    printArray (data, numLines);
    free (data);
  }
  if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      FILE * file = fopen (argv[i], "r");
      if (file == NULL) {
        fprintf(stderr, "Error: Could not open file.\n");
        return EXIT_FAILURE;
      }
      readFile (file);
      if (fclose(file) != 0) {
        fprintf(stderr, "Error: Failed to close the input file!\n");
        return EXIT_FAILURE;
      }
    }
  }
  return EXIT_SUCCESS;
}
