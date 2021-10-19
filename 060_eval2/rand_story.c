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
* readStory reads each line of a story and passes it into findBlank() along with 
*   an array of categories
*
* input: file is the file to be read
* input: categories is an array of category_t that will fill in the blanks for the story
*/
void readStory (FILE * file, catarray_t * categories) {
  char * line = NULL;
  size_t size;
  while (getline (&line, &size, file) >= 0) {
    findBlank (line, categories);
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
  catarray_t * arrayCat = malloc (sizeof (*arrayCat));
  category_t * categories = NULL;
  size_t n_cats = 0;
  arrayCat->arr = categories;
  arrayCat->n = n_cats;

  while (getline (&line, &size, file) >= 0) {
    char * category;
    char * word;
    parseWords (line, &category, ':', &word);
    //call function that either adds word to category or creates new category
    //printf ("Num of Categories: %zu\n", n_cats);
    addCategories (arrayCat, &category, &word);
    //add category to array
    /*for (size_t i = 0; i < arrayCat->n; i++) {
      for (size_t j = 0; j < arrayCat->arr[i].n_words; j++) {
        printf ("\tWords[%zu]: %s\n", j, arrayCat->arr[i].words[j]);
      }
    }*/
  }
  free (line);

  return arrayCat;
}

/**
* findBlank takes a line from an input file and prints everything to stdout,
*   words enclosed by '_' represent categories that will be replaced by with words 
*   from the respective category, found in categories, before being printed
*
* input: line is a line read from an input file
* input: categories is an array of category_t that will fill in the blanks for the story
*/
void findBlank (char * line, catarray_t * categories) {
  char * story = NULL;
  while ((story = strchr (line, '_')) != NULL) {
    char * always = strndup (line, (story - line));
    fprintf (stdout, "%s", always);
    free (always);

    char * category = getCategory(story);
    fprintf (stdout, "%s", chooseWord (category, categories));
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
}

void addCategories (catarray_t * arrayCat, char ** category, char ** word) {
  int catExists = 0;
  //printf ("Pairs: %s : %s\n", category, word);
  //category_t * categories = arrayCat;
  for (size_t i = 0; i < arrayCat->n; i++) {
      //printf ("Array Cat: %s - Param Cat: %s\n", arrayCat->arr[i].name, category);
    if (!strcmp(arrayCat->arr[i].name, *category)) {
      //printf ("Adding to category\n");
      size_t n_words = arrayCat->arr[i].n_words;
      arrayCat->arr[i].words = realloc (arrayCat->arr[i].words, (n_words + 1) * sizeof (arrayCat->arr[i].words));
      arrayCat->arr[i].words[n_words] = *word;
      arrayCat->arr[i].n_words = n_words + 1;
      catExists = 1;
      free (*category);
      break;
    }
  }
  if (catExists == 0) {
    arrayCat->arr = realloc (arrayCat->arr, (arrayCat->n + 1) * sizeof (*arrayCat->arr));
    /*category_t * newCategory = malloc (sizeof(*newCategory));
    newCategory->name = *category;
    char ** words = malloc (sizeof (*words));
    words[0] = *word;
    newCategory->words = words;
    newCategory->n_words = 1;
    arrayCat->arr[arrayCat->n] = *newCategory;*/
    category_t newCategory;
    newCategory.name = *category;
    char ** words = malloc (sizeof (*words));
    words[0] = *word;
    newCategory.words = words;
    newCategory.n_words = 1;
    arrayCat->arr[arrayCat->n] = newCategory;
    arrayCat->n += 1;
  }
}
//Return category of name else return NULL?
/*char * swapBlank (char * categoryBlank) {
  return chooseWord (categoryBlankk)
}*/

/**
* freeCategories frees the memory allocated for all fields inside categories
*   including memory allocated inside each category
*
* input: categories is a pointer to type catarray_t that contains an array of categories
*/
void freeCategories (catarray_t * categories) {
  for (size_t i = 0; i < categories->n; i++) {
    for (size_t j = 0; j < categories->arr[i].n_words; j++) {
      free (categories->arr[i].words[j]);
    }
    free (categories->arr[i].words);
    free (categories->arr[i].name);
  }
  free (categories->arr);
  free (categories);
}
