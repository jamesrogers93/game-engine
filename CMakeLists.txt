cmake_minimum_required(VERSION 2.8.4)

project(game-engine)

# Options
#option(THIS_SYSTEM "Build for this system" ON)
option(IOS "Build for iOS" OFF)
option(ANDROID "Build for ANDROID" OFF)

if(IOS)
	message(STATUS "Compiling for iOS")
elseif(ANDROID)
	message(STATUS "Compiling for Android")
else()
	message(STATUS "Compiling for this system")
endif()

# Output library location
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# cmake modules
set(CMAKE_MODULE_PATH
    "${CMAKE_SOURCE_DIR}/cmake/modules"
)

# include game-engine directories
include_directories(${CMAKE_SOURCE_DIR}/game-engine/include)


# Find all source files
file(GLOB_RECURSE INC_FILES ${PROJECT_SOURCE_DIR}/game-engine/include/game-engine/*.h)
file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/game-engine/src/*.cpp)


add_subdirectory(game-engine)

