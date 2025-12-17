#!/usr/bin/env sh

echo setting up make file using cmake...

cmake -S . -B build

cd build

echo Compiling and executing gl code...

make

cd ../bin

./OpenGL
