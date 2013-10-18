#!/bin/bash

DEMENTIAL=4
ATTS=64
_VECTOR=$((1024 * 2 * 2 * 2))
VECTOR_N=16
THRS_N=4

rm -rf tests
mkdir tests
make
cp par_app tests/.
cp seq_app tests/.
cd tests

echo "THREADS;NUMBER OF POINTS;TIME" > parallel_out
echo "NUMBER OF POINTS;TIME" > sequential_out

VECTOR=$_VECTOR
for i in $(seq 1 $VECTOR_N)
do
  TIME=0
  for attempt in $(seq 1 $ATTS)
  do
    echo "$VECTOR;$attempt" >> attempt
    tmp=`./seq_app --pairs $VECTOR --time 1`
    tmp2=`echo $tmp | cut -d \; -f 2`
    PI=`echo $tmp | cut -d \; -f 1`
    echo $tmp >> attempt
    TIME=$(echo "$TIME+$tmp2" | bc -l)
  done

  TIME=$(echo "$TIME/$ATTS.0" | bc -l)
  echo "$VECTOR;$TIME;$PI"
  echo "$VECTOR;$TIME;$PI" >> sequential_out

  VECTOR=$(($VECTOR *2))
  sleep 5
done

sleep 60

VECTOR=$_VECTOR
for i in $(seq 1 $VECTOR_N)
do
  THR=2
  for k in $(seq 1 $THRS_N)
  do
    TIME=0
    rm -f attempt*

    for attempt in $(seq 1 $ATTS)
    do
      echo "$THR;$VECTOR;$attempt" >> attempt
      tmp=`mpirun -np $THR ./par_app --pairs $VECTOR --time 1`
      TIME=`echo $tmp | cut -d \; -f 2`
      PI=`echo $tmp | cut -d \; -f 1`
      echo $tmp >> attempt
      TIME=$(echo "$TIME+$tmp2" | bc -l)
    done

    TIME=$(echo "$TIME/$ATTS.0" | bc -l)
    echo "$THR;$VECTOR;$TIME;$PI"
    echo "$THR;$VECTOR;$TIME;$PI" >> parallel_out

    THR=$((THR * 2))
    sleep 10
  done

  VECTOR=$(($VECTOR * 2))
  sleep 30
done

