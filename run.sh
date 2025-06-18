#!/bin/bash

if [ ! -d build ]; then
    echo "No build directory found. Configuring CMake..."
    cmake -S . -B build
fi

if cmake --build build; then
    echo "Build Suceeded. Running program..."
    ./build/Snake
else
    echo "Build failed!! Skipping program."
    exit 1
fi
