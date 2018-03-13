#!/usr/bin/env bash

function throw () { echo "fatal: $1"; echo "exit 1"; exit 1; }

pushd "$( dirname "${BASH_SOURCE[0]}" )";
pushd "..";

BUILD_DIR="build-flappy-sdl-ci";
[[ -e "$BUILD_DIR" ]] && throw "'$BUILD_DIR' is existed!";

mkdir "$BUILD_DIR" || throw "could not make directory '$BUILD_DIR'";

cd "$BUILD_DIR";
cmake ../flappybird-sdl || throw "cmake failed!";
make || throw  "make failed!";

cd ..;
rm "$BUILD_DIR" -rf || throw "could not clean build directory!";

echo "build-flappybird-sdl.sh done!";
exit 0;
