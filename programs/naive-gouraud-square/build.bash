#!/bin/bash

obj=../../lib

# we will just include every object file in that directory
g++ -o main main.cpp -I../../lib/ -lSDL -std=c++11 ${obj}/*.o -lSDL_gfx
