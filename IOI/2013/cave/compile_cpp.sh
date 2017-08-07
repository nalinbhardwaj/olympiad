#!/bin/bash

NAME=cave

/usr/bin/g++ -DEVAL -o $NAME grader.cpp $NAME.cpp
