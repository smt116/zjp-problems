#!/bin/bash

DEMENTIAL=4
ATTS=64
_DEMENTIAL=16
DEMENTIAL_N=7
THRS_N=4

rm -rf tests
mkdir tests
make
cp par_app tests/.
cp seq_app tests/.
cd tests

echo "THREADS;DEMENTIAL SIZE;TIME" > parallel_out
echo "DEMENTIAL SIZE;TIME" > sequential_out

DEMENTIAL=$_DEMENTIAL
for i in $(seq 1 $DEMENTIAL_N)
do
  TIME=0
  for attempt in $(seq 1 $ATTS)
  do
    echo "$DEMENTIAL;$attempt" >> attempt
    tmp=`./seq_app --size $DEMENTIAL`
    echo $tmp >> attempt
    TIME=$(echo "$TIME+$tmp" | bc -l)
  done

  TIME=$(echo "$TIME/$ATTS.0" | bc -l)
  echo "$DEMENTIAL;$TIME"
  echo "$DEMENTIAL;$TIME" >> sequential_out

  DEMENTIAL=$(($DEMENTIAL * 2))
done

sleep 30

DEMENTIAL=$_DEMENTIAL
for i in $(seq 1 $DEMENTIAL_N)
do
  echo "DEMENTIAL: $DEMENTIAL"
  THR=2
  for k in $(seq 1 $THRS_N)
  do
    TIME=0
    rm -f attempt*

    for attempt in $(seq 1 $ATTS)
    do
      echo "$THR;$DEMENTIAL;$attempt" >> attempt
      tmp=`mpirun -np $THR ./par_app --size $DEMENTIAL`
      echo $tmp >> attempt
      TIME=$(echo "$TIME+$tmp" | bc -l)
    done

    TIME=$(echo "$TIME/$ATTS.0" | bc -l)
    echo "$THR;$DEMENTIAL;$TIME"
    echo "$THR;$DEMENTIAL;$TIME" >> parallel_out

    THR=$((THR * 2))
    sleep 3
  done

  DEMENTIAL=$(($DEMENTIAL * 2))
  sleep 10
done

