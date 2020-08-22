#!/bin/bash
trap exit ERR

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

cd ../../
export DEBUG=YES
make
cd $DIR
./../../../../deps/valgrind-install/bin/valgrind --leak-check=yes --log-file=./log.txt ../../main.exe
