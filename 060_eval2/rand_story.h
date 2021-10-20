#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"
//any functions you want your main to use

void error (const char * message);
FILE * readFile (char * filename);
void closeFile (FILE * file);
void readStory (FILE * file, catarray_t * categories, int reuseWords);
catarray_t * readWords (FILE * file);
void findBlank (char * line, catarray_t * categories, category_t * usedWords, int reuseWords);
char * getCategory (char * blank);
void parseWords (char * line, char ** category, char ** word);
void addCategories (catarray_t * arrayCat, char ** category, char ** word);
void preventReuse (catarray_t * categories, char * category, char * word);
void freeCategories (catarray_t * categories);
void freeUsedWords (category_t * usedWords);

#endif
