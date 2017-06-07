# macOS Library

add_definitions(-D__macOS__)

# Include OpenGL
find_package(OpenGL REQUIRED)

# Include GLM
find_package (glm REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})

add_library(libGameEngine.macOS ${INC_FILES} ${SRC_FILES})

install(TARGETS libGameEngine.macOS DESTINATION lib)
install(FILES ${INC_FILES} DESTINATION include)

# Link Libraries
target_link_libraries(libGameEngine.macOS ${OPENGL_LIBRARY})