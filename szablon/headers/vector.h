/*
 * Maciej Małecki
 * smt116@gmail.com
 */
#ifndef SMT__LOCAL_VECTOR_LIB
#define SMT__LOCAL_VECTOR_LIB

  typedef struct Vector {
    int size;
    double *data;
  } Vector;

  Vector *new_vector(int);

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
  double reduce_vector(Vector *, int, int);
  void randomize_vector(Vector *, int);

#endif
