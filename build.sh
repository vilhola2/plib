#!/bin/bash

BUILD_TYPE=RELEASE
EXPORT_COMPILE_COMMANDS="OFF"
EXTRA_ARGS=""
VERBOSE=0

for arg in "$@"; do
    case $arg in
        -d)
            BUILD_TYPE=DEBUG
            EXPORT_COMPILE_COMMANDS="ON"
            ;;
        -install-dir=*)
            EXTRA_ARGS="$EXTRA_ARGS -DCMAKE_INSTALL_PREFIX=${arg#*=}"
            ;;
        -v)
            VERBOSE=1
            ;;
    esac
done

echo "Using build type: $BUILD_TYPE"

rm -rf lib/
mkdir -p build
cd build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=$EXPORT_COMPILE_COMMANDS -DCMAKE_BUILD_TYPE=$BUILD_TYPE $EXTRA_ARGS ..

if [ "$EXPORT_COMPILE_COMMANDS" = "ON" ]; then
    mv compile_commands.json ..
fi

GENERATOR=$(grep '^CMAKE_GENERATOR:' CMakeCache.txt | cut -d= -f2)

echo "CMake Generator: $GENERATOR"

if [[ "$GENERATOR" == *"Ninja"* ]]; then
    (( VERBOSE )) && ninja -v || ninja
elif [[ "$GENERATOR" == *"Makefiles"* ]]; then
    make VERBOSE=$VERBOSE
fi
