#!/bin/bash
killall -9 nc
killall -9 nc
killall -9 nc
RANGE=500
number=$RANDOM
let "number %= $RANGE"
let "number += 2048"
echo "Port # $number"

./show Port Number "$number"
nc 127.0.0.1 "$number" -q 1 | sudo nice -5 ./rabbit  -window 800x600 -noframe -position 1366x0  | ./controll -slowwork -window 1366x768 -position 0x0 -noframe -sleep 1 | nc  -l "$number" -k -q 1
killall -9 nc
killall -9 nc
killall -9 nc



