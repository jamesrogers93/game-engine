cmake_minimum_required(VERSION 2.8.4)

set (CMAKE_CXX_STANDARD 11)

# Options
#option(THIS_SYSTEM "Build for this system" ON)
#option(IOS "Build for iOS" OFF)
#option(ANDROID "Build for ANDROID" OFF)

if(IOS)
	message(STATUS "Compiling for iOS")
elseif(ANDROID)
	message(STATUS "Compiling for Android")
else()
	message(STATUS "Compiling for this system")
endif()

# Output library location
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)

# cmake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

# Game Engine
add_subdirectory(game-engine)

# Game Engine Test
add_subdirectory(tests)
