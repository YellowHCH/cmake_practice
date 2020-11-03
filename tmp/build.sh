#! /bin/sh
cd build
rm -rf *
cmake ..
make
cp test ../
cd ../
