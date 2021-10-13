#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "rand_story.h"

//strchr (string, character)- return pointer to first occurance of character
//strndup (string, n)- copy of string up until n

void error (const char * message) {
  fprintf (stderr, "Error: %s\n", message);
  exit (EXIT_FAILURE);
}

FILE * readFile (char * filename) {
  FILE * file = fopen (filename, "r");
  if (file == NULL) {
    error ("Failed to open file.");
  }
  return file;
}

void closeFile (FILE * file) {
  if (fclose (file) != 0) {
    error ("Failed to close file.");
  }
}

void readLine (FILE * file) {
  char * line = NULL;
  size_t size;
  while (getline (&line, &size, file) >= 0) {
    findBlank (line);
  }
  free (line);
}

void findBlank (char * line) {
  char * story = NULL;
  while ((story = strchr (line, '_')) != NULL) {
    char * always = strndup (line, (story - line));
    fprintf (stdout, "%s", always);
    free (always);

    char * category = getCategory(story);
    fprintf (stdout, "%s", chooseWord (category, NULL));
    free (category);
    line = strchr (++story, '_');
    line++;
  }
  fprintf (stdout, "%s", line);
}

char * getCategory (char * blank) {
  blank++;
  char * underscore = strchr (blank, '_');
  if (underscore == NULL) {
    error ("Blanks must begin and end with a '_'.");
  }
  return strndup (blank, (underscore - blank));  
}

//Return category of name else return NULL?
/*char * swapBlank (char * categoryBlank) {
  return chooseWord (categoryBlankk)
}

void printStory () {

}*/
