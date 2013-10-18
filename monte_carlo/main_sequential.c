/*
 * Maciej Małecki
 * smt116@gmail.com
 */
#include "lib.h"

int main(int argc, char *argv[]) {

  unsigned long long int total_pairs = 64;
  int verbose = 0,
      show_time = 0;
  double tmp_from_args = 0;

  get_long_from_args("--pairs", &total_pairs, argc, argv);
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
    printf("Total pairs: %llu\n", total_pairs);
  }

  {
    Vector *pairs = new_vector(total_pairs * 2);
    randomize_vector(pairs, 1);

    if(verbose) {
      print_vector(pairs, "pairs: ");
    }

    Time *t = new_time();
    start_time(t);

    double PI = 4 * ((double) count_points_in_circle(pairs) / total_pairs);

    stop_time(t);

    if(!show_time) {
      printf("%0.16lf\n", PI);
    } else {
      printf("%0.16lf;%0.16lf\n", PI, get_time(t));
    }

    delete_time(t);
    delete_vector(pairs);
  }

  return 0;
}
