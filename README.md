# Game Engine

[![Build Status](https://travis-ci.org/jamesrogers93/game-engine.svg?branch=master)](https://travis-ci.org/jamesrogers93/game-engine)

A multi-platform game engine.

## Install the required dependencies

### macOS and iOS

~~~~
brew update
brew install glm
~~~~

### Linux

~~~~
sudo apt-get install libglm-dev  
sudo apt-get install libglew-dev
~~~~


## Building the engine

To build for unix
~~~~
mkdir build
cd ./build
cmake ..
make
~~~~

To build for iOS
~~~~
mkdir build.ios
cd ./build.ios
cmake -G Xcode -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchains/ios.toolchain.cmake ..
xcodebuild -scheme GameEngine build
~~~~
