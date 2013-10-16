/*
 * Maciej Małecki
 * smt116@gmail.com
 */
#ifndef SMT__LOCAL_MATRIX_LIB
#define SMT__LOCAL_MATRIX_LIB

  #include "vector.h"

  typedef struct Matrix {
    int n;
    int m;
    double *data;
  } Matrix;

  Matrix *new_matrix(int, int);
  void delete_matrix(Matrix *);
  void set_matrix_with_var(Matrix *, double);
  void set_matrix_with_vars(Matrix *, double *);
  void print_matrix(Matrix *, char *);
  Matrix *product_matrix(Matrix *, Matrix *);

  #define index (i*p->m)+k

#endif
