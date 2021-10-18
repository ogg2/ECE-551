#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"
//any functions you want your main to use
#define WORDS 1
#define STORY 2

void error (const char * message);
FILE * readFile (char * filename);
void closeFile (FILE * file);
void readStory (FILE * file, catarray_t * categories);
catarray_t * readWords (FILE * file);
void findBlank (char * line, catarray_t * categories);
char * getCategory (char * blank);
void parseWords (char * line, char ** category, int delim, char ** word);
void addCategories (catarray_t * arrayCat, char * category, char * word);
void freeCategories (catarray_t * categories);

#endif
