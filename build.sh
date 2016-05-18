#!/bin/sh
echo Clearing
rm -rf build
echo Making build dir...
mkdir build
cd build
echo Running cmake...
cmake ../src
echo building...
make
echo running...
./ratebook --docroot .. --http-address 0.0.0.0 --http-port 8080