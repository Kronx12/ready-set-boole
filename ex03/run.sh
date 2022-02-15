#!/bin/sh

# Get name
NAME=ex03

# Compile
clang++ -Wall -Wextra -Werror -I. Graph.cpp $NAME.cpp -o $NAME

# Run
./$NAME

# Clear
rm -rf $NAME