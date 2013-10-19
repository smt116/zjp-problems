#!/bin/bash

ATTS=64
_GRANULATION=64
GRANULATION_N=26
THRS_N=4

rm -rf tests
mkdir tests
make
cp par_app tests/.
cp seq_app tests/.
cd tests

echo "THREADS;GRANULATION;TIME;INTEGRAL" > parallel_out
echo "GRANULATION;TIME;INTEGRAL" > sequential_out

date
GRANULATION=$_GRANULATION
for i in $(seq 1 $GRANULATION_N)
do
  TIME=0
  INTEGRAL=0
  for attempt in $(seq 1 $ATTS)
  do
    echo "$GRANULATION;$attempt" >> attempt
    tmp=`./seq_app -n $GRANULATION --time 1`
    tmp_time=`echo $tmp | cut -d \; -f 2`
    tmp_integral=`echo $tmp | cut -d \; -f 1`
    echo $tmp >> attempt
    TIME=$(echo "$TIME+$tmp_time" | bc -l)
    INTEGRAL=$(echo "$INTEGRAL+$tmp_integral" | bc -l)
  done

  TIME=$(echo "$TIME/$ATTS.0" | bc -l)
  INTEGRAL=$(echo "$INTEGRAL/$ATTS.0" | bc -l)
  echo "$GRANULATION;$TIME;$INTEGRAL"
  echo "$GRANULATION;$TIME;$INTEGRAL" >> sequential_out

  GRANULATION=$(($GRANULATION *2))
  sleep 5
done
date
sleep 30
date
GRANULATION=$_GRANULATION
for i in $(seq 1 $GRANULATION_N)
do
  THR=2
  for k in $(seq 1 $THRS_N)
  do
    TIME=0
    INTEGRAL=0
    rm -f attempt*

    for attempt in $(seq 1 $ATTS)
    do
      echo "$THR;$GRANULATION;$attempt" >> attempt
      tmp=`mpirun -np $THR ./par_app -n $GRANULATION --time 1`
      tmp_time=`echo $tmp | cut -d \; -f 2`
      tmp_integral=`echo $tmp | cut -d \; -f 1`
      echo $tmp >> attempt
      TIME=$(echo "$TIME+$tmp_time" | bc -l)
      INTEGRAL=$(echo "$INTEGRAL+$tmp_integral" | bc -l)
    done

    TIME=$(echo "$TIME/$ATTS.0" | bc -l)
    INTEGRAL=$(echo "$INTEGRAL/$ATTS.0" | bc -l)
    echo "$THR;$GRANULATION;$TIME;$INTEGRAL"
    echo "$THR;$GRANULATION;$TIME;$INTEGRAL" >> parallel_out

    THR=$((THR * 2))
    sleep 3
  done

  GRANULATION=$(($GRANULATION * 2))
  sleep 10
done
date
