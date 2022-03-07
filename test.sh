#!/bin/bash

for file in test/*a.txt
do
    ./build/matrix < ${file/a.txt/.txt} | diff $file -
done
