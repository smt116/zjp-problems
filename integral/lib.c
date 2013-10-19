/*
 * Maciej Małecki
 * smt116@gmail.com
 */
#include "lib.h"

void get_double_from_args(char *option, double *value, int argc, char **argv) {
  int i = 0;

  while(i < argc) {
    if(!strcmp(argv[i], option)) {
      *value = atof(argv[++i]);
    }
    i++;
  }
}

void get_long_from_args(char *option, long long int *value, int argc, char **argv) {
  int i = 0;

  while(i < argc) {
    if(!strcmp(argv[i], option)) {
      *value = atoll(argv[++i]);
    }
    i++;
  }
}

double f(double x) {
  return exp(-(x * x));
}

double integral(double a, double b, long long int n) {
  unsigned long long int i;
  double integral = 0,
         a1,
         b1;

  for(i=0; i < n - 1; i++) {
    a1 = a + (b - a) * ((double) i / n),
    b1 = a + (b - a) * ((double) (i + 1) / n);
    integral += (b1 - a1) * (f(a1) + f(b1)) / 2;
  }

  return integral;
}
