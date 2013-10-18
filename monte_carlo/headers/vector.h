/*
 * Maciej Małecki
 * smt116@gmail.com
 */
#ifndef SMT__LOCAL_VECTOR_LIB
#define SMT__LOCAL_VECTOR_LIB

  typedef struct Vector {
    unsigned long long int size;
    double *data;
  } Vector;

  Vector *new_vector(unsigned long long int);

  /*
   * Be sure that p->size >= q->size!
   */
  Vector *add_vectors(Vector *, Vector *);
  void set_vector_with_var(Vector *, double);
  void set_vector_with_vars(Vector *, double *);
  void print_vector(Vector *, char *);
  void delete_vector(Vector *);
  void multiply_vector_by(Vector *, double);
  Vector *multiply_vectors(Vector *, Vector *);
  double reduce_vector(Vector *, unsigned long long int, unsigned long long int);
  void randomize_vector(Vector *, unsigned long long int);

#endif
