#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "rand_story.h"

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
* return: FILE * is the file that has been opened and can now be read
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
*   an array of categories, it also creates a category to story previous words printed
*
* input: file is the file to be read
* input: categories is an array of category_t that will fill in the blanks for the story
* input: reuseWords indicates if the program was run with a "-n" argument [step4 specific]
*/
void readStory (FILE * file, catarray_t * categories, int reuseWords) {
  char * line = NULL;
  size_t size;

  category_t * usedWords = malloc (sizeof (*usedWords));
  char ** used = NULL;
  usedWords->name = "used";
  usedWords->words = used;
  usedWords->n_words = 0;
  
  while (getline (&line, &size, file) >= 0) {
    findBlank (line, categories, usedWords, reuseWords);
  }
  freeUsedWords (usedWords);
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
    parseWords (line, &category, &word);
    addCategories (arrayCat, &category, &word);
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
* input: usedWords is a pointer to a category of words already printed
* input: reuseWords indicates if the program was run with a "-n" argument [step4 specific]
*/
void findBlank (char * line, catarray_t * categories, category_t * usedWords, int reuseWords) {
  char * story = NULL;
  while ((story = strchr (line, '_')) != NULL) {
    char * always = strndup (line, (story - line));
    fprintf (stdout, "%s", always);
    free (always);

    char * category = getCategory(story);
    int prevWord;
    char * thisWord;
    char * extraLetters = NULL;
    if ((prevWord = strtol (category, &extraLetters, 10)) > 0 && *extraLetters == '\0') {
      int index = usedWords->n_words - prevWord;
      if (index < 0) {
        error ("Index out of bounds. Tried to look at previous word that doesn't exist'.");
      }
      thisWord = strdup (usedWords->words[index]);
    } else {
      thisWord = strdup (chooseWord (category, categories));
    }

    fprintf (stdout, "%s", thisWord);
    usedWords->words = realloc (usedWords->words, (1 + usedWords->n_words) * sizeof (*usedWords->words));
    usedWords->words[usedWords->n_words] = thisWord;
    usedWords->n_words++;
    if (reuseWords == 0) {
      preventReuse (categories, category, thisWord);
    }

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

/**
* parseWords takes a line read from a file, the string before ':' is stored into category
*   the string after ':' is stored into word
*
* input: line is a line read from a file in the format category:word
* input: category is pointer to a string, text before ':' will be stored here
* input: word is a poitner to a string, text after ':' will be stored here
*/
void parseWords (char * line, char ** category, char ** word) {
  char * string;

  if ((string = strchr (line, ':')) != NULL) {
    *category = strndup (line, (string - line)); 
    string++;
    char * end = strchr (string, '\n');
    *word = strndup (string, (size_t) (end - string)); 
  }
  if (string == NULL) {
    error ("Line not in format category:word.");
  }
}

/**
* addCategories builds a catarray_t, if a category already exists the word is added to the existing 
*   category, else a new category is created add added to arrayCat
*
* input: arrayCat is a pointer to catarray_t containing the categories read from an input file
* input: category is a pointer to the name of a category
* input: word is a pointer to a string that will be added to a an existing category or a new category
*/
void addCategories (catarray_t * arrayCat, char ** category, char ** word) {
  int catExists = 0;
  //search arrayCat to see if category already exists
  //if it does, add word to the existing category
  for (size_t i = 0; i < arrayCat->n; i++) {
    if (!strcmp(arrayCat->arr[i].name, *category)) {
      size_t n_words = arrayCat->arr[i].n_words;
      arrayCat->arr[i].words = realloc (arrayCat->arr[i].words, (n_words + 1) * 
          sizeof (arrayCat->arr[i].words));
      arrayCat->arr[i].words[n_words] = *word;
      arrayCat->arr[i].n_words = n_words + 1;
      catExists = 1;
      free (*category);
      break;
    }
  }
  //if category does not yet exist, create a new category and add it to arrayCat
  if (catExists == 0) {
    arrayCat->arr = realloc (arrayCat->arr, (arrayCat->n + 1) * sizeof (*arrayCat->arr));
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

/**
* preventReuse removes all instances of word from its category if reuseWords == 0
*
* input: categories is a pointer to an array of category_t
* input: category is the category name that we need to move all instances of word from
* input: word is the word that needs to be removed so it cannot be reused
*/
void preventReuse (catarray_t * categories, char * category, char * word) {
  for (size_t i = 0; i < categories->n; i++) {
    if (!strcmp (categories->arr[i].name, category)) {
      for (size_t j = 0; j < categories->arr[i].n_words; j++) {
        if (!strcmp (categories->arr[i].words[j], word)) {
          free (categories->arr[i].words[j]);
          for (size_t k = j; k < categories->arr[i].n_words - 1; k++) {
            categories->arr[i].words[k] = categories->arr[i].words[k + 1];
          }
          categories->arr[i].n_words--;
          break;
        }
      }
      categories->arr[i].words = realloc (categories->arr[i].words, categories->arr[i].n_words * 
          sizeof (*categories->arr[i].words));
      break;
    }
  }
}

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

/**
* freeUsedWords frees memory in a category
*
* input: usedWords is a pointer to a category that will have it's memory freed
*/
void freeUsedWords (category_t * usedWords) {
  for (size_t i = 0; i < usedWords->n_words; i++) {
    free (usedWords->words[i]);
  }
  free (usedWords->words);
  free (usedWords);
}
