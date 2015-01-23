#!/bin/sh
#nc  127.0.0.1 1235 | ./controll -window 800x600 | nc 127.0.0.1 1234 
#nc  192.168.1.114 1235 | ./controll -slowwork -window 1366x768 -position 0x0 -noframe -sleep 1 -nosendexit | nc 192.168.1.114 1234 
nc  127.0.0.1 1235 | ./controll  -window 1366x768 -position 0x0 -noframe -sleep 1 -nosendexit | nc 127.0.0.1 1234 

