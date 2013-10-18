#!/bin/bash

DEMENTIAL=4
ATTS=512
_VECTOR=32
VECTOR_N=9
THRS_N=5

rm -rf tests
mkdir tests
make
cp par_app tests/.
cp seq_app tests/.
cd tests

echo "THREADS;VECTOR SIZE;TIME" > parallel_out
echo "VECTOR SIZE;TIME" > sequential_out

VECTOR=$_VECTOR
for i in $(seq 1 $VECTOR_N)
do
  TIME=0
  for attempt in $(seq 1 $ATTS)
  do
    echo "$VECTOR;$attempt" >> attempt
    tmp=`./seq_app --size $VECTOR`
    echo $tmp >> attempt
    TIME=$(echo "$TIME+$tmp" | bc -l)
  done

  TIME=$(echo "$TIME/$ATTS.0" | bc -l)
  echo "$VECTOR;$TIME"
  echo "$VECTOR;$TIME" >> sequential_out

  VECTOR=$(($VECTOR *2))
done

VECTOR=$_VECTOR
for i in $(seq 1 $VECTOR_N)
do
  echo "VECTOR: $VECTOR"
  THR=2
  for k in $(seq 1 $THRS_N)
  do
    TIME=0
    rm -f attempt*

    for attempt in $(seq 1 $ATTS)
    do
      echo "$THR;$VECTOR;$attempt" >> attempt
      tmp=`mpirun -np $THR ./par_app --size $VECTOR`
      echo $tmp >> attempt
      TIME=$(echo "$TIME+$tmp" | bc -l)
    done

    TIME=$(echo "$TIME/$ATTS.0" | bc -l)
    echo "$THR;$VECTOR;$TIME"
    echo "$THR;$VECTOR;$TIME" >> parallel_out

    THR=$((THR * 2))
  done

  VECTOR=$(($VECTOR * 2))
done

