#!/usr/bin/env bash

set -e

rm -rf build/
mkdir build
cd build

cmake ..
cmake --build .

./engo-net server
