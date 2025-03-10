#!/bin/bash

#check buildl dir
if [! -d build]
then
	mkdir build
fi

#generate cmake files
cmake -O . -B ./build -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=ON

#copy asset files to output dir
cp -R "./resouce" "./build/bin/assets"

#compile priject
cd build && cmake --build .
echo compilation successful