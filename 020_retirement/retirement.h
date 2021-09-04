#ifndef RETIREMENT_H
#define RETIREMENT_H

struct _retire_info {
  int month;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;
void retirement (int startAge, double initial, retire_info working, retire_info retired);
double calculations (double current_balance, retire_info stage_of_life);

#endif
