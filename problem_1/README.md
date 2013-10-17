Design and implement an MPI/C program for the matrix/vector product.
* Given are:
    a cluster consisting of p=4 networked processors,
    a square n=16,
    (16 x 16) matrix called A and a vector x.
* Write a sequential code for matrix/vector product.
    Generate some matrix and a vector with integer components
* Initially A and x are located on process 0.
* Divide A into 4 row-strips each with 4 rows.
* Move x and one strip to process 1,2 and 3.
* Let each process compute a part of the product vector y.
* Assemble the product vector on process 0 and let process 0
    print the final result vector y.
