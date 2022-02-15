#!/bin/sh

# Get name
NAME=ex04

# Compile
clang++ -Wall -Wextra -Werror -I. Graph.cpp $NAME.cpp -o $NAME

# Run
./$NAME

# Clear
rm -rf $NAME