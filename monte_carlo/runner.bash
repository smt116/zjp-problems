#!/bin/bash

ATTS=128
_PAIRS=$((1024 * 8))
PAIRS_N=14
THRS_N=4

rm -rf tests
mkdir tests
make
cp par_app tests/.
cp seq_app tests/.
cd tests

echo "THREADS;NUMBER OF POINTS;TIME" > parallel_out
echo "NUMBER OF POINTS;TIME" > sequential_out

date
PAIRS=$_PAIRS
for i in $(seq 1 $PAIRS_N)
do
  TIME=0
  PI=0
  for attempt in $(seq 1 $ATTS)
  do
    echo "$PAIRS;$attempt" >> attempt
    tmp=`./seq_app --pairs $PAIRS --time 1`
    tmp_time=`echo $tmp | cut -d \; -f 2`
    tmp_pi=`echo $tmp | cut -d \; -f 1`
    echo $tmp >> attempt
    TIME=$(echo "$TIME+$tmp_time" | bc -l)
    PI=$(echo "$PI+$tmp_pi" | bc -l)
  done

  TIME=$(echo "$TIME/$ATTS.0" | bc -l)
  PI=$(echo "$PI/$ATTS.0" | bc -l)
  echo "$PAIRS;$TIME;$PI"
  echo "$PAIRS;$TIME;$PI" >> sequential_out

  PAIRS=$(($PAIRS *2))
  sleep 10
done
date
sleep 120
date
PAIRS=$_PAIRS
for i in $(seq 1 $(($PAIRS_N - 1)))
do
  THR=2
  for k in $(seq 1 $THRS_N)
  do
    TIME=0
    PI=0
    rm -f attempt*

    for attempt in $(seq 1 $ATTS)
    do
      echo "$THR;$PAIRS;$attempt" >> attempt
      tmp=`mpirun -np $THR ./par_app --pairs $PAIRS --time 1`
      tmp_time=`echo $tmp | cut -d \; -f 2`
      tmp_pi=`echo $tmp | cut -d \; -f 1`
      echo $tmp >> attempt
      TIME=$(echo "$TIME+$tmp_time" | bc -l)
      PI=$(echo "$PI+$tmp_pi" | bc -l)
    done

    TIME=$(echo "$TIME/$ATTS.0" | bc -l)
    PI=$(echo "$PI/$ATTS.0" | bc -l)
    echo "$THR;$PAIRS;$TIME;$PI"
    echo "$THR;$PAIRS;$TIME;$PI" >> parallel_out

    THR=$((THR * 2))
    sleep 5
  done

  PAIRS=$(($PAIRS * 2))
  sleep 15
done
date
