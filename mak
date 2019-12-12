#!/bin/bash
#USAGE: ./mak OR ./mak clean
if [[ "$#" -eq 1 && "$1" -eq "clean" ]]
then

    rm -f *.o *.a

else

    for f in "bst-vector"
    do
        gcc -Wall -c -o $f.o $f.c
    done

    ar rcs libbstvector.a *.o

    gcc -Wall -o unit-test unit-test.c libbstvector.a
fi
