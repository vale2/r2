#!/bin/sh
rm ~/libsdl/project/jni/application/src/controll.cpp
cp ./andrcontroll.cpp ~/libsdl/project/jni/application/src/controll.cpp
cd ~/libsdl/
./build.sh -r
cd ~/r2/ungl
