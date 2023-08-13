#!/bin/bash
cd bin/debug
echo -- DEBUG
make -j8
cd ../release
echo -- RELEASE
make -j8
cd ../web/debug
echo -- WEB DEBUG
make -j8
cd ../release
echo -- WEB RELEASE
make -j8