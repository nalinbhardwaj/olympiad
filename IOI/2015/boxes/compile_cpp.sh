#!/bin/bash

problem=boxes

g++ -DEVAL -std=gnu++14 -o $problem -Wall -Wshadow -Wextra -Wconversion grader.cpp $problem.cpp
