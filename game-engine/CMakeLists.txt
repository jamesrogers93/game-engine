
# Add platform specific definitions
if(IOS)
	add_definitions(-D__IOS__)
	set(PLATFORM “iOS”)
elseif(ANDROID)
	add_definitions(-D__ANDROID__)
	set(PLATFORM “android”)
else()
	add_definitions(-D__MACOS__)
	set(PLATFORM “macOS”)
endif()

# Platform specific external libraries
if(IOS OR ANDROID)
	# Include OpenGLES
	find_package(OpenGLES REQUIRED)
	#include_directories("${OPENGLES_INCLUDE_DIR}")
	list(APPEND PLATFORM_LIBRARIES
            ${OPENGLES_LIBRARIES}
        )
else()
	# Include OpenGL
	find_package(OpenGL REQUIRED)
	include_directories("${OPENGL_INCLUDE_DIR}")
	list(APPEND PLATFORM_LIBRARIES
            ${OPENGL_LIBRARY}
        )
endif()

# Include GLM (same for all platforms)
find_package (glm REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})

# Platform specific toolchain
#if(IOS)
#set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/toolchains)
#endif()

add_library(GameEngine ${INC_FILES} ${SRC_FILES})

install(TARGETS GameEngine DESTINATION ../lib/$(PLATFORM))
install(FILES ${INC_FILES} DESTINATION include)

# Link Libraries
#target_link_libraries(GameEngine ${PLATFORM_LIBRARIES})


