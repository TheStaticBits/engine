#!/bin/bash
rm -r bin

# Create bin, debug, and release folders
mkdir bin
mkdir bin/debug
mkdir bin/release

# Emscripten web compilations
mkdir bin/web
mkdir bin/web/debug
mkdir bin/web/release