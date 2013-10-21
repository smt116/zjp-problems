/*
 * Maciej Małecki
 * smt116@gmail.com
 */
#include "lib.h"
#include "mpi.h"

int main(int argc, char *argv[]) {

  long long int n = 32;
  double a = -2.0,
         b = 2.0;
  int verbose = 0,
      show_time = 0,
      rank,
      size;

  {
    double tmp_from_args = 0;
    get_double_from_args("-a", &a, argc, argv);
    get_double_from_args("-b", &b, argc, argv);
    get_long_from_args("-n", &n, argc, argv);
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
  }

  if(verbose && rank == 0) {
    printf("a:\t%4.2lf\nb:\t%4.2lf\nn:\t%llu\n", a, b, n);
  }

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  {
    double local_a = a + ((double) rank / (double) size) * (b - a),
           local_b = a + ((double) (rank + 1) / (double) size) * (b - a),
           local_integral = 0,
           global_integral = 0;
    long long int local_n = n / size;

    Time *t = new_time();
    start_time(t);

    local_integral = integral(local_a, local_b, local_n);

    if(verbose) {
      printf("[%i] Hi chef! my part for [%lf, %lf] is: %.16lf, right?\n", rank, local_a, local_b, local_integral);
    }

    MPI_Reduce(&local_integral, &global_integral,
               1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    stop_time(t);
    if(show_time && rank == 0) {
      printf("%.32lf;%.16lf\n", global_integral, get_time(t));
    } else if(rank == 0) {
      printf("%.32lf\n", global_integral);
    }

    delete_time(t);
  }

  MPI_Finalize();

  return 0;
}
