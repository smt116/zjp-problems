/*
 * Maciej Małecki
 * smt116@gmail.com
 */
#ifndef SMT__LOCAL_MATRIX_LIB
#define SMT__LOCAL_MATRIX_LIB

  #include "vector.h"

  typedef struct Matrix {
    unsigned long long int n;
    unsigned long long int m;
    double *data;
  } Matrix;

  Matrix *new_matrix(unsigned long long int, unsigned long long int);
  void delete_matrix(Matrix *);
  void set_matrix_with_var(Matrix *, double);
  void set_matrix_with_vars(Matrix *, double *);
  void print_matrix(Matrix *, char *);
  Matrix *product_matrix(Matrix *, Matrix *);
  void randomize_matrix(Matrix *, unsigned long long int);

#endif
