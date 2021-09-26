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
      error ("Country name too long.");
      //fprintf (stderr, "Error: Country name too long.\n");
      //exit (EXIT_FAILURE);
    }
      ans.name[i++] = character;
      line++;
  }
  ans.name[i] = '\0';
  line++;

  /*if ((character = *line) == '\0') {
    error ("No population.");
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
      uint64_t overflowCheck = population;
      uint64_t addDigit = character - '0';
      population = population * 10 + addDigit;
      if (population < overflowCheck) {
        error ("Overflow - Population does not fit in uint64_t.");
      }
    }
    line++;
  }
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
    if (day != n_days) {
      sevenDayTotal -= *firstDay;
      sevenDayTotal += *data;
    }
    avg++;
    data++;
    firstDay++;
  } while (day++ < n_days);

}

/**
 * calcCumulative calculates the cumulative cases per 100k population for an array of days up to a given day
 * 
 * input: data contains the daily number of cases for an array of days
 * input: n_days specifies how many data points (days) are stored in data array and will be sotred in cum array
 * input: pop contains the total population size
 * input: cum stores the cumulative cases per 100k population for an array of days up to that given day
 */
void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
  if (data == NULL || cum == NULL) {
    error ("Input array is NULL.");
  }
  if (n_days < 0) {
    return;
  }

  size_t day = 0;
  uint64_t cumulativeCases = 0;
  double ratio = pop / 100000;

  while (day++ < n_days) {
    cumulativeCases += *data;
    *cum = cumulativeCases / ratio;;
    cum++;
    data++;
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
  if (countries == NULL || data == NULL) {
    error ("Input array is NULL.");
  }
  if (n_countries < 1 || n_days < 1) {
    error ("No data to calculate country with most cases.");
  }
  
  char * country_most;
  unsigned most_cases = 0;
  int tie = 1;
  size_t country = 0;

  while (country < n_countries) {
    for (size_t day = 0; day < n_days; day++) {
      unsigned dailyCases = data[country][day];
      char * thisCountry = countries[country].name;
      if (dailyCases > most_cases) {
        tie = 0;
        country_most = thisCountry;
        most_cases = dailyCases;
      } else if (dailyCases == most_cases && country_most != thisCountry) {
        tie = 1;
      } else {
        ;
      }
    }
    country++;
  }

  if (tie == 1) {
    printf ("There is a tie between at least two countries\n");
    return;
  }

  printf("%s has the most daily cases with %u\n", country_most, most_cases);
}
