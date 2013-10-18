/*
 * Maciej Małecki
 * smt116@gmail.com
 */
#include "lib.h"
#include "sequential.h"

void sequential_matrix_product(Matrix *product, Matrix *A, Matrix *x) {
  unsigned long long int i, k, l;

  for(i=0; i < A->n; i++) {
    for(k=0; k < A->m; k++) {
      for(l=0; l < x->m; l++) {
        product->data[(l * product->n) + k] +=
          A->data[(i * A->n) + k] * x->data[(l * x->n) + k];
      }
    }
  }
}
