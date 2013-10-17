/*
 * Maciej Małecki
 * smt116@gmail.com
 */
#include "lib.h"
#include "parallel.h"

void parallel_matrix_product(Matrix *product, Matrix *A, Matrix *x) {
  int i,
      k,
      l;

/*
    if(rank == 0) {
        MPI_Send(i, 1, MPI_INT, (i % size), 0, MPI_COMM_WORLD);
      }
    } else {
      MPI_Recv(i, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    }
    */
  for(i=0; i < A->n; i++) {
    for(k=0; k < A->m; k++) {
      for(l=0; l < x->m; l++) {
        product->data[(l * product->n) + k] +=
          A->data[(i * A->n) + k] * x->data[(l * x->n) + k];
      }
    }
  }

}
