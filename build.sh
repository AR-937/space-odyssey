#!/bin/bash

mkdir -p bin

g++ -std=c++17 -O2 -march=native -pthread \
    src/main.cpp src/scene.cpp src/renderer.cpp \
    -o bin/ASpaceOdyssey \
    -lsfml-graphics -lsfml-window -lsfml-system

echo "Build completed. Run with ./bin/ASpaceOdyssey" 