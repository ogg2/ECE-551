#include "pandemic.h"
#include <stdio.h>
#include <ctype.h>
#include <errno.h>


/**
 * error takes an error message, prints it out, and exits the program
 *
 * input - message is the error message that will be printed to command line
 */
void error (const char * message) {
  fprintf (stderr, "Error: %s\n", message);
  exit (EXIT_FAILURE);
}


/**
 * parseLine takes an input string that contains a country name and population
 * and inputs it into a struct of type country_t 
 *
 * input: line is a string containing country name and population
 *
 * return: country_t is struct containing the country name and population 
 */
country_t parseLine(char * line) {
  //WRITE ME
  country_t ans;
  int i = 0;
  int character;
  while ((character = *line) != ',') {
    if (i > 62) {
      error ("Error: Country name too long.");
      //fprintf (stderr, "Error: Country name too long.\n");
      //exit (EXIT_FAILURE);
    }
    //if (isalpha(character) || character == ' ') {
      ans.name[i] = character;
      line++;
      i++;
    //}
  }
  ans.name[i] = '\0';
  line++;

  /*if ((character = *line) == '\0') {
    fprintf (stderr, "Error: Population for %s must be a number.\n", ans.name);
    exit (EXIT_FAILURE);
  }*/

  uint64_t population = 0;
  while ((character = *line) != '\0') {
    if (isspace(character)) { //MAYBE CHECK IF PREV CHARACTER WAS NOT 0-9
      ;
    } else if (character == '-') {
      error ("Population count cannot be negative.");
      //fprintf (stderr, "Error: Population count for %s cannot be negative.\n", ans.name);
      //exit (EXIT_FAILURE);
    } else if (character < '0' || character > '9') {
      error ("Population must be a number.");
      //fprintf (stderr, "Error: Population for %s must be a number.\n", ans.name);
      //exit (EXIT_FAILURE);
    } else {
      int overflow = population;
      int addDigit = character - '0';
      population = population * 10 + addDigit;
      if ((population - addDigit) / 10 != overflow) {
        error ("Population does not fit in uint64_t.");
        //fprintf (stderr, "Error: Population for %s does not fit in uint64_t.\n", ans.name);
        //exit (EXIT_FAILURE);
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

/**
 * calcRunningAvg calculates the seven day running of case data
 *
 * input: data contains the daily number of cases for an array of days
 * input: n_days specifies how many data points (days) are stored in data array
 * input: avg stores the results of the seven day running average as calculated by the function
 */
void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
  if (data == NULL || avg == NULL) {
    error ("Input array is NULL.");
    //fprintf (stderr, "Input array is NULL.\n");
    //exit (EXIT_FAILURE);
  }
  if (n_days < 7) {
    return;
  }
  unsigned sevenDayTotal = 0;
  unsigned * firstDay = data;

  size_t day;
  for (day = 0; day < 7; day++) {
    sevenDayTotal += *data;
    data++; 
  }

  do {
    *avg = (double) sevenDayTotal / 7;
    avg++;
    sevenDayTotal = sevenDayTotal - *firstDay + *data;
    data++;
    firstDay++;
  } while (day++ < n_days);

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
