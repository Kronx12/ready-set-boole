#!/bin/sh

# Get name
NAME=ex00

# Compile
clang++ -Wall -Wextra -Werror $NAME.cpp -o $NAME

# Run
./$NAME

# Clear
rm -rf $NAME