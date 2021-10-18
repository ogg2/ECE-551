#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "rand_story.h"

//strchr (string, character)- return pointer to first occurance of character
//strndup (string, n)- copy of string up until n

/**
 * error takes an error message, prints it out, and exits the program
 *
 * input: message is the error message that will be printed to command line
 */
void error (const char * message) {
  fprintf (stderr, "Error: %s\n", message);
  exit (EXIT_FAILURE);
}

/**
* readFile takes a filename and returns a FILE or fails if there was an error
*
* input: filename is the name of the file to be opened
*/
FILE * readFile (char * filename) {
  FILE * file = fopen (filename, "r");
  if (file == NULL) {
    error ("Failed to open file.");
  }
  return file;
}

/**
* closeFile closes a file and fails if there was an error
*
* input: file is a file to be closed
*/
void closeFile (FILE * file) {
  if (fclose (file) != 0) {
    error ("Failed to close file.");
  }
}

/**
* readLine reads each line of a story and passes it into findBlank()
*
* input: file is the file to be read
*/
void readLine (FILE * file) {
  char * line = NULL;
  size_t size;
  while (getline (&line, &size, file) >= 0) {
    findBlank (line);
  }
  free (line);
}

/**
* readWords reads each line of file containing categories and words then stores them into a catarray_t
*
* input: file is the file to be read
* return: catarray_t * is an array of category_t read from the input file
*/
catarray_t * readWords (FILE * file) {
  char * line = NULL;
  size_t size;
  category_t * categories = NULL;
  size_t n_cats = 0;

  while (getline (&line, &size, file) >= 0) {
    char * category;
    char * word;
    parseWords (line, &category, ':', &word);
    //call function that either adds word to category or creates new category
    printf ("Num of Categories: %zu\n", n_cats);
    addCategories (&categories, &n_cats, category, word);
    //add category to array
    for (size_t i = 0; i < categories[0].n_words; i++) {
      printf ("\tWords[%zu]: %s\n", categories[0].n_words, categories[0].words[i]);
    }
  }
  free (line);

  catarray_t * ans = malloc (sizeof (*ans));
  ans->arr = categories;
  ans->n = n_cats;
  return ans;
}

/**
* findBlank takes a line from an input file and prints everything to stdout,
*   words enclosed by '_' represent categories that will be replaced by with words 
*   from the respective category before being printed
*
* input: line is a line read from an input file
*/
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

/**
* getCategory takes a category in the format _category_ and removes the '_'s
*
* input: blank is a category string to be cleaned
* return: char * is a the category without the '_'s
*/
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
  char * string;

  if ((string = strchr (line, delim)) != NULL) {
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
    
void addCategories (category_t ** arrayCat, size_t * n_elem, char * category, char * word) {
  int catExists = 0;
  printf ("Pairs: %s : %s\n", category, word);
  //category_t * categories = arrayCat;
  for (size_t i = 0; i < *n_elem; i++) {
      printf ("Array Cat: %s - Param Cat: %s\n", arrayCat[i]->name, category);
    if (!strcmp(arrayCat[i]->name, category)) {
      printf ("Adding to category\n");
      size_t n_words = arrayCat[i]->n_words;
      arrayCat[i]->words = realloc (arrayCat[i]->words, (n_words + 1) * sizeof (*arrayCat[i]->words));
      arrayCat[i]->words[n_words] = word;
      arrayCat[i]->n_words = n_words + 1;
      catExists = 1;
      break;
    }
  }
  if (catExists == 0) {
    *arrayCat = realloc (*arrayCat, (*n_elem + 1) * sizeof (**arrayCat));
    category_t * newCategory = malloc (sizeof(*newCategory));
    newCategory->name = category;
    char ** words = malloc (sizeof (*words));
    words[0] = word;
    newCategory->words = words;
    newCategory->n_words = 1;
    printf ("%s\n", newCategory->words[newCategory->n_words - 1]);
    printf ("%zu\n", *n_elem);
    *arrayCat[*n_elem] = *newCategory;
    printf ("Print marker\n");
    *n_elem += 1;
  }
}
//Return category of name else return NULL?
/*char * swapBlank (char * categoryBlank) {
  return chooseWord (categoryBlankk)
}*/
