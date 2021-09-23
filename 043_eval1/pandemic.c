#include "pandemic.h"
#include <stdio.h>
#include <ctype.h>
#include <errno.h>

/**
 * parseLine takes an input string that contains a country name and population
 * and inputs it into a struct of type country_t 
 *
 * input: line - string from an input file containing country name and population
 *
 * return: country_t - struct containing the country name and population 
 */
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

  uint64_t population = 0;
  while ((character = *line) != '\0') {
    if (isspace(character)) { //MAYBE CHECK IF PREV CHARACTER WAS NOT 0-9
      ;
    } else if (character == '-') {
      fprintf (stderr, "Error: Population count for %s cannot be negative.\n", ans.name);
      exit (EXIT_FAILURE);
    } else if (character < '0' || character > '9') {
      fprintf (stderr, "Error: Population for %s must be a number.\n", ans.name);
      exit (EXIT_FAILURE);
    } else {
      int overflow = population;
      int addDigit = character - '0';
      population = population * 10 + addDigit;
      if ((population - addDigit) / 10 != overflow) {
        fprintf (stderr, "Error: Population for %s does not fit in uint64_t.\n", ans.name);
        exit (EXIT_FAILURE);
      }
    }
    line++;
  }

 // errno = 0;
  //uint64_t population = atol (line);
  /*if (errno != 0 || errno == ERANGE) {
    fprintf (stderr, "Error: Population count for %s is not a number.\n", ans.name);
    perror ("The error was: ");
    exit (EXIT_FAILURE);
  }
  if (population == 0) {
    fprintf (stderr, "Error: Population count for %s is not a number.\n", ans.name);
    exit (EXIT_FAILURE);
  }*/
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
