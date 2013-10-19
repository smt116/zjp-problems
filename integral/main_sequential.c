/*
 * Maciej Małecki
 * smt116@gmail.com
 */
#include "lib.h"

int main(int argc, char *argv[]) {

  long long int n = 8;
  double a = -2.0,
         b = 2.0;
  int verbose = 0,
      show_time = 0;

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

  if(verbose) {
    printf("a:\t%4.2lf\nb:\t%4.2lf\nn:\t%llu\n", a, b, n);
  }

  {
    Time *t = new_time();
    start_time(t);

    double value = integral(a, b, n);

    stop_time(t);
    if(show_time) {
      printf("%.32lf;%.16lf\n", value, get_time(t));
    } else {
      printf("%.32lf\n", value);
    }

    delete_time(t);
  }

  return 0;
}
