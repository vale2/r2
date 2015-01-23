#!/bin/sh
killall -9 nc
killall -9 nc
killall -9 nc
killall -9 nc

./startit.sh&
sleep 1
./startcontroll.sh
killall -9 nc
killall -9 nc
killall -9 nc
killall -9 nc

