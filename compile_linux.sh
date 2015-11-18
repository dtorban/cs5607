#!/bin/bash

mkdir build
cd build
cmake ..
make
printf "\n\nBuild Complete. Use \"./build/bin/GLFW_App\" to run example.\n\n"
