# Install script for directory: /Users/James/Documents/University/Advanced_Computer_Science/Year_1/Dissertation/Application/game-engine/game-engine.macOS

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/James/Documents/University/Advanced_Computer_Science/Year_1/Dissertation/Application/game-engine/build/game-engine.macOS/Debug/liblibGameEngine.macOS.a")
    if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liblibGameEngine.macOS.a" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liblibGameEngine.macOS.a")
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liblibGameEngine.macOS.a")
    endif()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/James/Documents/University/Advanced_Computer_Science/Year_1/Dissertation/Application/game-engine/build/game-engine.macOS/Release/liblibGameEngine.macOS.a")
    if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liblibGameEngine.macOS.a" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liblibGameEngine.macOS.a")
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liblibGameEngine.macOS.a")
    endif()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/James/Documents/University/Advanced_Computer_Science/Year_1/Dissertation/Application/game-engine/build/game-engine.macOS/MinSizeRel/liblibGameEngine.macOS.a")
    if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liblibGameEngine.macOS.a" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liblibGameEngine.macOS.a")
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liblibGameEngine.macOS.a")
    endif()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/James/Documents/University/Advanced_Computer_Science/Year_1/Dissertation/Application/game-engine/build/game-engine.macOS/RelWithDebInfo/liblibGameEngine.macOS.a")
    if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liblibGameEngine.macOS.a" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liblibGameEngine.macOS.a")
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liblibGameEngine.macOS.a")
    endif()
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/Users/James/Documents/University/Advanced_Computer_Science/Year_1/Dissertation/Application/game-engine/include/Core/Engine/Engine.h"
    "/Users/James/Documents/University/Advanced_Computer_Science/Year_1/Dissertation/Application/game-engine/include/Core/Modules/CoreModule.h"
    "/Users/James/Documents/University/Advanced_Computer_Science/Year_1/Dissertation/Application/game-engine/include/Core/Modules/Graphics/Geometry.h"
    "/Users/James/Documents/University/Advanced_Computer_Science/Year_1/Dissertation/Application/game-engine/include/Core/Modules/Graphics/Graphics.h"
    "/Users/James/Documents/University/Advanced_Computer_Science/Year_1/Dissertation/Application/game-engine/include/Core/Modules/Graphics/Shader.h"
    "/Users/James/Documents/University/Advanced_Computer_Science/Year_1/Dissertation/Application/game-engine/include/Core/Modules/Graphics/Vertex.h"
    "/Users/James/Documents/University/Advanced_Computer_Science/Year_1/Dissertation/Application/game-engine/include/Core/Scene/Scene.h"
    "/Users/James/Documents/University/Advanced_Computer_Science/Year_1/Dissertation/Application/game-engine/include/Core/Scene/SceneManager.h"
    "/Users/James/Documents/University/Advanced_Computer_Science/Year_1/Dissertation/Application/game-engine/include/Defines/OpenGL.h"
    )
endif()

