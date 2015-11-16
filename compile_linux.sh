#!/bin/bash

mkdir build
cd build
cmake ..
make
printf "\n\nBuild Complete. Use \"./build/BasicTest\" to run example.\n\n"
