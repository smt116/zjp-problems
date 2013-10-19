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

  #include "headers/vector.h"
  #include "headers/matrix.h"
  #include "headers/time.h"

  #define MALLOC(type, n) (type*)malloc((n)*sizeof(type))

  void get_double_from_args(char *, double *, int, char **);
  void get_long_from_args(char *, unsigned long long int *, int, char **);

#endif
