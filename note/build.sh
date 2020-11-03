#! /bin/sh
cd build
rm -rf *
cmake ..
make
cp more_effective_c++ ../
cp test ../
cd ../
