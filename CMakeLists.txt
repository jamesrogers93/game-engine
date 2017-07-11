cmake_minimum_required(VERSION 3.1)

set (CMAKE_CXX_STANDARD 11)

# Options
option(TESTS "Build test project" OFF)

#option(THIS_SYSTEM "Build for this system" ON)
#option(IOS "Build for iOS" OFF)
#option(ANDROID "Build for ANDROID" OFF)

# Add platform specific definitions
if(IOS)
	message(STATUS "Compiling for iOS")
	add_definitions(-D__IOS__)
	set(PLATFORM_NAME "ios")
elseif(ANDROID)
	message(STATUS "Compiling for Android")
	add_definitions(-D__ANDROID__)
	set(PLATFORM_NAME "android")
elseif(UNIX AND APPLE)
	message(STATUS "Compiling for macOS")
	add_definitions(-D__MACOS__)
	set(PLATFORM_NAME "macos")
elseif(UNIX AND NOT APPLE)
	message(STATUS "Compiling for Linux")
	add_definitions(-D__LINUX__)
	set(LINUX TRUE)
	set(PLATFORM_NAME "linux")
endif()

# Output locations
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)

# cmake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

# Game Engine
add_subdirectory(game-engine)

# Game Engine Test
if(TESTS)
	add_subdirectory(tests)
endif()