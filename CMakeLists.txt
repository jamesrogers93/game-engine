cmake_minimum_required(VERSION 3.0)

project(game-engine)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE INC_FILES ${PROJECT_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_subdirectory(game-engine.macOS)

