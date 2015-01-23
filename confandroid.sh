#!/bin/sh
#cd /home/7/libsdl
#rm /home/7/libsdl/project/jni/application/src
#ln -s /home/7/r2/ungl project/jni/application/controll
#ln -s  controll project/jni/application/src
#cp /home/7/r2/ungl/AndroidAppSettings.cfg /home/7/libsdl/
#./build.sh
#cd /home/7/r2/ungl/
#rm /home/7/libsdl/project/jni/application/controll
#rm /home/7/libsdl/project/jni/application/src

cd /home/7/libsdl
rm -rf /home/7/libsdl/project/jni/application/controll/*
cp -R /home/7/r2/ungl/* /home/7/libsdl/project/jni/application/controll/
rm /home/7/libsdl/project/jni/application/controll/rabbit.cpp
rm /home/7/libsdl/project/jni/application/controll/snake.cpp

./build.sh -r
cd /home/7/r2/ungl/
