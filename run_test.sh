#!/bin/bash
echo "##### Compile to build executable"
make

# test with scanner
./scanner input01
echo "##### input01 test pass"
./scanner input02
echo "##### input02 test pass"
./scanner input03
echo "##### input03 test pass"
./scanner input04
echo "##### input04 test pass"
./scanner input05
echo "##### input05 test pass"