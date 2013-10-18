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

int point_in_circle(double x, double y, double z) {
  if((x * x) + (y * y) <= z) {
    return 1;
  } else {
    return 0;
  }
}

int count_points_in_circle(Vector *p) {
  int i,
      success = 0;

  for(i=0; i < p->size; i+=2) {
    success += point_in_circle(p->data[i], p->data[i + 1], 1);
  }

  return success;
}
