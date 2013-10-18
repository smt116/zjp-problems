/*
 * Maciej Małecki
 * smt116@gmail.com
 */
#include "lib.h"
#include "mpi.h"

int main(int argc, char *argv[]) {

  int total_pairs = 64,
      verbose = 0,
      show_time = 0,
      size,
      rank;
  double tmp_from_args = 0;

  get_double_from_args("--pairs", &tmp_from_args, argc, argv);
  if(tmp_from_args != 0) {
    total_pairs = (int) tmp_from_args;
    tmp_from_args = 0;
  }
  get_double_from_args("--verbose", &tmp_from_args, argc, argv);
  if(tmp_from_args != 0) {
    verbose = (int) tmp_from_args;
    tmp_from_args = 0;
  }
  get_double_from_args("--time", &tmp_from_args, argc, argv);
  if(tmp_from_args != 0) {
    show_time = (int) tmp_from_args;
    tmp_from_args = 0;
  }

  if(verbose) {
    printf("Total pairs: %u\n", total_pairs);
  }

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  Vector *pairs = new_vector(total_pairs * 2);

  if(rank == 0) {
    randomize_vector(pairs, 1);

    if(verbose) {
      print_vector(pairs, "pairs: ");
    }
  }

  int local_size = (total_pairs * 2) / size,
      local_points_in_circle = 0,
      points_in_circle = 0;
  Vector *local_pairs = new_vector(local_size);
  Time *t;

  if(rank == 0) {
    points_in_circle = 0;
    t = new_time();
    start_time(t);
  }

  MPI_Scatter(
    pairs->data,        local_size, MPI_DOUBLE,
    local_pairs->data,  local_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  local_points_in_circle = count_points_in_circle(local_pairs);

  MPI_Reduce(&local_points_in_circle,
             &points_in_circle,
             1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  if(rank == 0) {
    double PI = 4 * (points_in_circle / (double) total_pairs);

    stop_time(t);

    if(!show_time) {
      printf("%0.16lf\n", PI);
    } else {
      printf("%0.16lf;%0.16lf\n", PI, get_time(t));
    }

    delete_time(t);
  }

  delete_vector(local_pairs);
  delete_vector(pairs);

  MPI_Finalize();

  return 0;
}
