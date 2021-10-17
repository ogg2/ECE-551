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

catarray_t * readWords (FILE * file) {
  char * line = NULL;
  size_t size;
  category_t * arrayCat = NULL;
  size_t n_cats = 0;

  while (getline (&line, &size, file) >= 0) {
    char * word;
    char * category;
    parseWords (line, &category, ':', &word);
    printf ("READLINE: %s : %s\n", category, word);
    //call function that either adds word to category or creates new category
    addCategories (arrayCat, n_cats, category, word);
    //add category to array
    
  }
  free (line);
  return NULL;
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

/*catarray_t * parseWords (char * line) {
  catarray_t * categories = NULL;

  while (getline (&line, &size, line)) {
    
  }
}*/

void parseWords (char * line, char ** category, int delim, char ** word) {
  //int character;
  //size_t stringSize = 0;
  char * string;

  if ((string = strchr (line, delim)) != NULL) {
    //size_t length = string - line; 
    //*category = realloc (*category, length * sizeof (**category));
    //*category = malloc (length * sizeof (**category));
    *category = strndup (line, (string - line)); 
    string++;
    char * end = strchr (string, '\n');
    *word = strndup (string, (size_t) (end - string)); 
  }

  /*while ((character = *line) != c) {
    string = realloc (string, (1 + stringSize) * sizeof (*string));
    string[stringSize++] = character;
    line++;
  }

  string = realloc (string, (1 + stringSize) * sizeof (*string));
  string[stringSize] = '\0';
  return string;*/
}
    
void addCategories (category_t * arrayCat, size_t n_elem, char * category, char * word) {
  int catExits = 0;
  for (size_t i = 0; i < n_elem; i++) {
    if (!strcmp(arrayCat[i].name, category)) {
      size_t n_words = arrayCat[i].n_words;
      arrayCat[i].words = realloc (arrayCat[i].words, (n_words + 1) * sizeof (*arrayCat[i].words));
      arrayCat[i].words[n_words] = word;
      arrayCat[i].n_words = n_words + 1;
      catExits = 1;
      break;
    }
  }
  if (catExits == 0) {
    arrayCat = realloc (arrayCat, (n_elem + 1) * sizeof (*arrayCat));
    category_t * newCat = malloc (sizeof(*newCat));
    newCat->name = category;
    char ** words = malloc (sizeof (*words));
    words[0] = word;
    newCat->words = words;
    newCat->n_words = 1;
    arrayCat[n_elem] = *newCat;
  }
}
//Return category of name else return NULL?
/*char * swapBlank (char * categoryBlank) {
  return chooseWord (categoryBlankk)
}

void printStory () {

}*/
