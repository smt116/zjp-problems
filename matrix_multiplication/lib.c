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

void get_long_from_args(char *option, unsigned long long int *value, int argc, char **argv) {
  int i = 0;

  while(i < argc) {
    if(!strcmp(argv[i], option)) {
      *value = atoll(argv[++i]);
    }
    i++;
  }
}
