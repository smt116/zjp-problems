# Matrix multiplication

#### Tested on Sigma

Info | Value
--- | ---
Number of calls *for averaging time* | 64
Time of the whole test | 4h 41m
Time of sequential part of test | 2h 46m
Time of parallel part of test | 0h 13m

Time of the whole tests includes the sleep functions between 
sequential and parallel test and between changing size of data.

Time of each test is computed as `(TIME_1 + TIME_2 + ... + TIME_i) / number_of_calls`, where `i` is number of calls

## Sequential program:

DIMENSION (A[n, n] x B[n, n]) | TIME
--- | ---
16 | .00004652400000000000
32 | .00036968000000000000
64 | .00328370800000000000
128 | .03009969200000000000
256 | .24937857600000000000
512 | 3.13345063199999998593
**1024** | **149.66328576799999839531**

## Parallel program:

NUMBER OF THREADS | DIMENSION (A[n, n] x B[n, n]) | TIME
--- | --- | ---
2 | 16 | .00039854400000000000
4 | 16 | .00156840800000000000
8 | 16 | .00233679600000000000
16 | 16 | .00281548800000000000
2 | 32 | .00110215200000000000
4 | 32 | .00221693600000000000
8 | 32 | .00285568000000000000
16 | 32 | .00243788000000000000
2 | 64 | .00536822800000000000
4 | 64 | .00569316400000000000
8 | 64 | .01792634400000000000
16 | 64 | .00354096800000000000
2 | 128 | .02909130400000000000
4 | 128 | .01789232000000000000
8 | 128 | .02477298000000000000
16 | 128 | .02572591600000000000
2 | 256 | .18699104000000000000
4 | 256 | .09680470000000000000
8 | 256 | .06825912400000000000
16 | 256 | .09543014800000000000
2 | 512 | 1.37818376400000000781
4 | 512 | .70759718799999999843
8 | 512 | .42445419200000000000
16 | 512 | .51762281599999999843
2 | 1024 | 10.87124728400000003906
4 | 1024 | 5.49558770399999995625
**8** | **1024** | **3.10156440400000001562**
16 | 1024 | 3.39772541600000000000