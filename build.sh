#!/bin/bash
clang++ src/*.cpp -I src/ -std=c++11 -lsfml-{graphics,window,system} -o pacwoman