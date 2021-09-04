#include <stdlib.h>
#include <stdio.h>

#include "retirement.h"

/*struct _retire_info {
  int month;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;
*/

void retirement (int startAge, double initial, retire_info working, retire_info retired) {
  double current_balance = initial; 

  for (int i = 0; i < working.month; i++) {
    printf ("Age %3d month %2d you have $%.2lf\n", startAge / 12, startAge % 12, current_balance);
    current_balance = calculations(current_balance, working);
    startAge++;
  }

  for (int i = 0; i < retired.month; i++) {
    printf ("Age %3d month %2d you have $%.2lf\n", startAge / 12, startAge % 12, current_balance);
    current_balance = calculations(current_balance, retired);
    startAge++;
  }
}

double calculations (double current_balance, retire_info stage_of_life) {
  current_balance += current_balance * stage_of_life.rate_of_return;
  current_balance += stage_of_life.contribution;
  return current_balance;
}

int main (void) {
  retire_info working;
  working.month = 489;
  working.contribution = 1000;
  working.rate_of_return = .045 / 12;
  
  retire_info retired;
  retired.month = 384;
  retired.contribution = -4000;
  retired.rate_of_return = .01 / 12; 

  int age = 327;
  double savings = 21345;

  retirement (age, savings, working, retired);

  return EXIT_SUCCESS;
}
