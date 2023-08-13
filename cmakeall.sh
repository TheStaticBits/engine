#!/bin/bash
cd bin/debug
cmake -S ../..
cd ../release
cmake -S ../..
cd ../web/debug
emcmake cmake -S ../../..
cd ../release
emcmake cmake -S ../../..