#include "pandemic.h"
#include <stdio.h>
#include <ctype.h>

/**
* parseLine takes an input string that contains a country name and population
* and inputs it into a struct of type country_t 
* input: line - string from an input file containing country name and population
*
* return: country_t - struct containing the country name and population 
**/
country_t parseLine(char * line) {
  //WRITE ME
  country_t ans;
  int i = 0;
  char character;
  while ((character = *line) != ',') {
    if (i > 62) {
      fprintf (stderr, "Error: Country name too long.\n");
      exit (EXIT_FAILURE);
    }
    //if (isalpha(character) || character == ' ') {
      ans.name[i] = character;
      line++;
      i++;
    //}
  }
  ans.name[i] = '\0';
  line++;
  uint64_t population = atoi (line);
  if (population == 0) {
    fprintf (stderr, "Error: Population count for %s is not a number.\n", ans.name);
    exit (EXIT_FAILURE);
  }
  ans.population = population;

  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
}
