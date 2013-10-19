/*
 * Maciej Małecki
 * smt116@gmail.com
 */
#ifndef SMT__LOCAL_STATIC_LIB
#define SMT__LOCAL_STATIC_LIB

  #include <stdio.h>
  #include <stdlib.h>
  #include <math.h>
  #include <string.h>

  #include "../c-libs/headers/vector.h"
  #include "../c-libs/headers/matrix.h"
  #include "../c-libs/headers/time.h"

  #define MALLOC(type, n) (type*)malloc((n)*sizeof(type))

  void get_double_from_args(char *, double *, int, char **);
  void get_long_from_args(char *, unsigned long long int *, int, char **);
  int point_in_circle(double, double, double);
  unsigned long long int count_points_in_circle(Vector *);

#endif
