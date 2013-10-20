/*
 * Maciej Małecki
 * smt116@gmail.com
 */
#include "lib.h"
#include <mpi.h>

int main(int argc, char *argv[]) {

  unsigned long long int dimension_A = 16,
                         dimension_x = 1,
                         dimension = 0;

  int size,
      rank,
      verbose = 0;

  double tmp_from_args = 0,
         max_data_value = 1024;

  {
    get_long_from_args("-a", &dimension_A, argc, argv);
    get_long_from_args("-x", &dimension_x, argc, argv);
    get_long_from_args("--size", &dimension, argc, argv);
    if(dimension) {
      dimension_A = dimension_x = dimension;
    }
    get_double_from_args("--verbose", &tmp_from_args, argc, argv);
    if(tmp_from_args != 0) {
      verbose = (int) tmp_from_args;
      tmp_from_args = 0;
    }
    get_double_from_args("--maxvalue", &max_data_value, argc, argv);
  }

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  Matrix *A       = new_matrix(dimension_A, dimension_A),
         *x       = new_matrix(dimension_A, dimension_x),
         *product = new_matrix(A->m, x->m);
  Time *t = new_time();

  {
    set_matrix_with_var(A, 1);
    set_matrix_with_var(x, 1);
    set_matrix_with_var(product, 0);

    randomize_matrix(x, max_data_value);
  }

  if(rank == 0) {
    randomize_matrix(A, max_data_value);

    if(verbose) {
      print_matrix(A, "A");
      print_matrix(x, "x");
    }
  }

  start_time(t);
  unsigned long long int local_size = dimension_A * (dimension_A / size);

  Vector *local_row = new_vector(local_size),
         *local_column = new_vector(dimension_x * dimension_A);
  Matrix *local_sum = new_matrix((dimension_A / size), dimension_x);
  set_matrix_with_var(local_sum, 0);

  MPI_Scatter(
    A->data,          local_size, MPI_DOUBLE,
    local_row->data,  local_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  {
    unsigned long long int i,
                           k,
                           l;
    for(i=0, l=(i * x->m); i < x->m; i++) {
      for(k=0; k < x->n; k++, l++) {
        local_column->data[l] = x->data[(k * x->m) + i];
      }
    }

    if(verbose && rank == 0) {
      print_vector(local_column, "columns_from_x");
    }
    if(verbose) {
      print_vector(local_row, "rows_from_A   ");
    }

    for(i=0; i < dimension_x; i++) {
      for(k=0; k < dimension_A / size; k++) {
        Vector *c = vector_cut(local_column, (i * dimension_A), ((i + 1) * dimension_A)),
               *r = vector_cut(local_row, (k * dimension_A), ((k + 1) * dimension_A));

        Vector *m = multiply_vectors(r, c);
        double sum = reduce_vector(m, 0, m->size);
        local_sum->data[(i * local_sum->n) + k] = sum;

        if(verbose && rank == 0) {
          print_vector(c, "c");
          print_vector(r, "r");
          print_vector(m, "cr");
          printf("Reduced cr [%llu][%llu]: %lf\n\n", k, i, sum);
        }

        delete_vector(c);
        delete_vector(r);
        delete_vector(m);
      }
    }

    {
      int data_size = (dimension_A / size) * dimension_x;
      MPI_Gather(local_sum->data, data_size, MPI_DOUBLE,
                 product->data,   data_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }

    if(verbose && rank == 0) {
      print_matrix(A, "A");
      print_matrix(x, "x");
      print_matrix(product, "Ax");
    }

    if(rank == 0) {
      stop_time(t);
      printf("%0.16lf\n", get_time(t));
    }
  }

  delete_time(t);
  delete_vector(local_row);
  delete_vector(local_column);
  delete_matrix(local_sum);
  delete_matrix(product);
  delete_matrix(A);
  delete_matrix(x);

  MPI_Finalize();

  return 0;
}
