# Zaawansowane Języki Programowania (UG).

Problems:

* monte carlo (computing PI)
* integral (computing integral using trapezoid method)
* matrics multiplication

Sequential and parallel (using MPI) programs.

## Compilation - HowTo

#### Compile the static library (helper)

```bash
$ cd c-libs
$ make libs
```

#### integral

```bash
$ cd integral
$ make
```

#### monte_carlo

```bash
$ cd monte_carlo
$ make
```

#### matrix_multiplication

```bash
$ cd matrix_multiplication
$ make
```

## Running programs

**Program will not check if input data is correct!**

#### integral 

`f(x) = e^(-x^2)` -- you can provide another f(x) in `lib.c`

##### Sequential program

```bash
# a, b - [a, b]
# n - granularity (number of points between a and b)
$ ./seq_app -a -2.5 -b 2.5 -n 100
```

##### Parallel program (MPI)

```bash
# np - number of threads
# a, b - [a, b]
# n - granularity (number of points between a and b)
$ ./seq_app -a -2.5 -b 2.5 -n 100
$ mpirun -np 8 par_app -a -2.5 -b 2.5 -n 64
```

#### monte_carlo

##### Sequential program

```bash
# --pairs - number of points in [0, a] x [0,b]
# --time - print the time of computing
$ ./seq_app --pairs 1024 --time 1
```

##### Parallel program (MPI)

```bash
# -np - number of threads
# --pairs - number of points in [0, a] x [0,b]
# --time - print the time of computing
$ mpirun -np 8 par_app --pairs 1024 --time 1
```

#### matrix_multiplication

##### Sequential program

```bash
# -a - dimension of A[a, a]
# -x - dimension of x[a, x]
# --size - size = a = x (will overwrite a and x)
# --maxvalue - max value of each number in matrics (values are random)
$ ./seq_app --size 512
```

##### Parallel program (MPI)

```bash
# np - number of threads
# -a - dimension of A[a, a]
# -x - dimension of x[a, x]
# --size - size = a = x (will overwrite a and x)
# --maxvalue - max value of each number in matrics (values are random)
$ mpirun -np 8 par_app --size 512
```
