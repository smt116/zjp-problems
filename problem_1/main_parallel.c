/*
 * Maciej Małecki
 * smt116@gmail.com
 */
#include "lib.h"
#include "parallel.h"

int main(int argc, char *argv[]) {

  unsigned int demential_size = 16,
               verbose = 0;

  int size,
      rank;

  double tmp_from_args = 0,
         max_data_value = 1024;

  get_double_from_args("--size", &tmp_from_args, argc, argv);
  if(tmp_from_args != 0) {
    demential_size = (int) tmp_from_args;
    tmp_from_args = 0;
  }
  get_double_from_args("--verbose", &tmp_from_args, argc, argv);
  if(tmp_from_args != 0) {
    verbose = (int) tmp_from_args;
    tmp_from_args = 0;
  }
  get_double_from_args("--maxvalue", &max_data_value, argc, argv);

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  Matrix *A = new_matrix(demential_size, demential_size),
         *product = new_matrix(demential_size, 1);
  Vector *x = new_vector(demential_size);
  Time *t = new_time();

  set_matrix_with_var(product, 0);
  set_matrix_with_var(A, 0);
  randomize_vector(x, max_data_value);

  if(rank == 0) {
    randomize_matrix(A, max_data_value);

    if(verbose) {
      print_matrix(A, "A");
      print_vector(x, "x");
    }
  }

  start_time(t);
  unsigned int local_size = demential_size * (demential_size / size);

  Vector *local_row = new_vector(local_size),
         *local_x = new_vector(local_size),
         *tmp_multiplied;

  {
    int i;
    for(i=0; i < local_x->size; i++) {
      local_x->data[i] = x->data[i % demential_size];
    }
  }

  MPI_Scatter(
    A->data,          local_size, MPI_DOUBLE,
    local_row->data,  local_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  tmp_multiplied = multiply_vectors(local_row, local_x);
  double local_sum[demential_size / size];

  {
    int i;
    for(i=0; i < demential_size / size; i++) {
      local_sum[i] = reduce_vector(tmp_multiplied, (i * demential_size), ((i + 1) * demential_size));
    }
  }

  MPI_Gather(local_sum,     demential_size / size, MPI_DOUBLE,
             product->data, demential_size / size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  if(rank == 0) {
    stop_time(t);
    printf("%0.16lf\n", get_time(t));
  }

  if(verbose && rank == 0) {
    print_matrix(product, "Ax");
  }

  delete_time(t);

  delete_vector(local_row);
  delete_vector(local_x);
  delete_vector(tmp_multiplied);

  delete_matrix(product);
  delete_matrix(A);
  delete_vector(x);

  MPI_Finalize();

  return 0;
}
