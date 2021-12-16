#!/bin/bash

if [ -d build ]; then
  mkdir build
fi

cd build
cmake ..
make clean;make

cp socket_client ../
cp socket_server ../
