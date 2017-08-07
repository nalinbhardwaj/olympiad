#!/bin/bash

NAME=robots

/usr/bin/g++ -DEVAL -std=gnu++14 -o $NAME grader.cpp $NAME.cpp
