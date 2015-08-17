#!/bin/sh

cd ..
make clean all
sudo make install

echo; echo
cd test
cc -o zcaplibtest -g -Wall -fno-color-diagnostics -lnv -lzcap zcaplibtest.c
echo; echo

ktrace -i ./zcaplibtest
