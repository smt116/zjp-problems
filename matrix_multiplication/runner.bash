#!/bin/bash

DIMENSION=4
ATTS=64
_DIMENSION=16
DIMENSION_N=7
THRS_N=4

rm -rf tests
mkdir tests
make
cp par_app tests/.
cp seq_app tests/.
cd tests

echo "THREADS;DIMENSION SIZE;TIME" > parallel_out
echo "DIMENSION SIZE;TIME" > sequential_out

DIMENSION=$_DIMENSION
for i in $(seq 1 $DIMENSION_N)
do
  TIME=0
  for attempt in $(seq 1 $ATTS)
  do
    echo "$DIMENSION;$attempt" >> attempt
    tmp=`./seq_app --size $DIMENSION`
    echo $tmp >> attempt
    TIME=$(echo "$TIME+$tmp" | bc -l)
  done

  TIME=$(echo "$TIME/$ATTS.0" | bc -l)
  echo "$DIMENSION;$TIME"
  echo "$DIMENSION;$TIME" >> sequential_out

  DIMENSION=$(($DIMENSION * 2))
done

sleep 30

DIMENSION=$_DIMENSION
for i in $(seq 1 $DIMENSION_N)
do
  echo "DIMENSION: $DIMENSION"
  THR=2
  for k in $(seq 1 $THRS_N)
  do
    TIME=0
    rm -f attempt*

    for attempt in $(seq 1 $ATTS)
    do
      echo "$THR;$DIMENSION;$attempt" >> attempt
      tmp=`mpirun -np $THR ./par_app --size $DIMENSION`
      echo $tmp >> attempt
      TIME=$(echo "$TIME+$tmp" | bc -l)
    done

    TIME=$(echo "$TIME/$ATTS.0" | bc -l)
    echo "$THR;$DIMENSION;$TIME"
    echo "$THR;$DIMENSION;$TIME" >> parallel_out

    THR=$((THR * 2))
    sleep 3
  done

  DIMENSION=$(($DIMENSION * 2))
  sleep 10
done

