#!/bin/sh
killall -9 nc
killall -9 nc
killall -9 nc

nc  -l 1234 -k| ./rabbit  -window 800x600 -noframe  -position 1366x0  | nc  -l 1235 -k 
killall -9 nc
killall -9 nc
killall -9 nc

