# Game Engine

A multi-platform game engine.

## Building the engine

To build for MacOS
~~~~
mkdir build.macos
cd ./build.macos
cmake ..
~~~~

To build for iOS
~~~~
mkdir build.ios
cd ./build.ios
`cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchains/ios.toolchain.cmake ..`
~~~~
