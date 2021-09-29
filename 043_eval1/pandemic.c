#include "pandemic.h"
#include <stdio.h>
#include <ctype.h>


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

  //Country Name Parse
  while ((character = *line) != ',') {
    if (i > 62) {
      error ("Country name too long.");
    }
      ans.name[i++] = character;
      line++;
  }
  ans.name[i] = '\0';
  line++;

  //Country Population Parse
  uint64_t population = 0;
  int anyInput = 0;     //variable to make sure user did not leave out popualtion input 
  int positive = 1;     //variable to check if user input is negative
  while ((character = *line) != '\0' && character != ',') {
    if (isspace(character)) {
      if (anyInput == 1) {
        break;
      }
    } else if (character == '-') {
      positive = -1;
    } else if (character < '0' || character > '9') {
      error ("Population must be a number.");
    } else {
      uint64_t overflowCheck = population;
      uint64_t addDigit = character - '0';
      population = population * 10 + addDigit;
      anyInput = 1;
      if (population < overflowCheck) {
        error ("Overflow - Population does not fit in uint64_t.");
      }
    }
    line++;
  }
  if (anyInput == 0) {
    error ("No population for country.");
  }
  ans.population = population * positive;
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
  }
  if (n_days < 7) {
    return;
  }
  unsigned sevenDayTotal = 0;
  unsigned * firstDay = data;     //pointer to track front of array

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
 * input: n_days specifies how many data points (days) are stored in data array and will be stored in cum array
 * input: pop contains the total population size
 * input: cum stores the cumulative cases per 100k population for an array of days up to that given day
 */
void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
  if (data == NULL || cum == NULL) {
    error ("Input array is NULL.");
  }
  if (n_days < 1) {
    return;
  }

  unsigned cumulativeCases = 0;
  double ratio = pop / (double) 100000;

  for (size_t day = 0; day < n_days; day++) {
    cumulativeCases += *data;
    *cum = cumulativeCases / ratio;
    cum++;
    data++;
  }
}

/**
 * printCountryWithMax finds the maximum number of daily cases of all
 * countries represented in data, over the entire time period
 *
 * input: countries contains the list of countries represented in data
 * input: n_countries is the number of countries represented in data
 * input: data contains the number of daily cases for all countries,
 *        over the entire time period
 * input: n_days is the number of days of data for each country
 */
void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
  if (countries == NULL || data == NULL) {
    error ("Input array is NULL.");
  }
  if (n_countries < 1 || n_days < 1) {
    return;
  }
  
  char * country_most = countries[0].name;
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
