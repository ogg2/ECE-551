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
  //printf("Inside printArray\n");
  /*while (*data != NULL) {
    printf ("%s", *data);
    data++;
  }*/
  for (size_t i = 0; i < size; i++) {
    printf ("%s", data[i]);
  }
}

void readFile (FILE * file) {
  char * line = NULL;
  size_t sz;
  char ** data = NULL;
  size_t numLines = 0;
  while (getline (&line, &sz, file) >= 0) {
    data = realloc (data, (1 + numLines) * sizeof (*data));  
    data[numLines] = line;
    //printf ("Line: %s", data[numLines]);
    numLines++;
    line = NULL;
  }
  free (line);
  //printf("First line: %s\n", data[0]);
  sortData (data, numLines);
  printArray (data, numLines);
  free (data);
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  if (argc == 1) {
    ;
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
