#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"

//any functions you want your main to use

void error (const char * message);
FILE * readFile (char * filename);
void closeFile (FILE * file);
void readLine (FILE * file);
void findBlank (char * line);
char * getCategory (char * blank);

#endif
