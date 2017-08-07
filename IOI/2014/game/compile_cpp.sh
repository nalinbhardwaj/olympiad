#!/bin/bash

NAME=game

/usr/bin/g++ -DEVAL -std=gnu++14 -std=c++11 -o $NAME grader.cpp $NAME.cpp
