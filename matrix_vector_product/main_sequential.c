/*
 * Maciej Małecki
 * smt116@gmail.com
 */
#include "lib.h"
#include "sequential.h"

int main(int argc, char *argv[]) {

  unsigned long long int demential_A = 16,
                         demential_x = 1,
                         demential = 0;
  int verbose = 0;
  double tmp_from_args = 0,
         max_data_value = 1024;

  {
    get_long_from_args("-a", &demential_A, argc, argv);
    get_long_from_args("-x", &demential_x, argc, argv);
    get_long_from_args("--size", &demential, argc, argv);
    if(demential) {
      demential_A = demential_x = demential;
    }
    get_double_from_args("--verbose", &tmp_from_args, argc, argv);
    if(tmp_from_args != 0) {
      verbose = (int) tmp_from_args;
      tmp_from_args = 0;
    }
    get_double_from_args("--maxvalue", &max_data_value, argc, argv);
  }

  Matrix *A = new_matrix(demential_A, demential_A);
  Matrix *x = new_matrix(demential_A, demential_x);

  {
    randomize_matrix(A, max_data_value);
    randomize_matrix(x, max_data_value);

    if(verbose) {
      print_matrix(A, "A");
      print_matrix(x, "x");
    }
  }

  {
    Matrix *product = new_matrix(A->m, x->m);
    set_matrix_with_var(product, 0);

    Time *t = new_time();
    {
      start_time(t);
      sequential_matrix_product(product, A, x);
      stop_time(t);

      printf("%0.16lf\n", get_time(t));
      delete_time(t);
    }

    if(verbose) {
      print_matrix(product, "Ax");
    }

    delete_matrix(product);
  }
  delete_matrix(A);
  delete_matrix(x);

  return 0;
}
