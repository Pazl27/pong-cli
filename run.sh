#!/bin/bash

if [ ! -d "build" ]; then
  mkdir build
fi

# Change directory to build
cd build || { echo "Directory 'build' not found"; exit 1; }

# Run cmake
cmake .. || { echo "cmake configuration failed"; exit 1; }

# Run make
make || { echo "make failed"; exit 1; }

# Run the executable
./target/app || { echo "Failed to run the executable"; exit 1; }
