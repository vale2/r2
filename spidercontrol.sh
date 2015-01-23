#!/bin/sh
#nc  127.0.0.1 1235 | ./controll -window 800x600 | nc 127.0.0.1 1234 
nc  192.168.1.254 1235 | ./controll  | nc 192.168.1.254 1234 

