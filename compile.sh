#!/bin/sh
# Usage: ./compile.sh        - release build
#        ./compile.sh debug  - debug build with sanitizers

if [ "$1" = "debug" ]; then
    g++ -std=c++17 -Wall -Wextra -g -fsanitize=address,undefined main.cpp -o main.out
else
    g++ -std=c++17 -Wall -Wextra -O2 main.cpp -o main.out
fi
