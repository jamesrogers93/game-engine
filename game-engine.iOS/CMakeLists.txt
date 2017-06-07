# iOS Executable

add_definitions(-D__APPLE__)

add_library(libGameEngine.iOS ${INC_FILES} ${SRC_FILES})

install(TARGETS libGameEngine.iOS DESTINATION lib)
install(FILES ${INC_FILES} DESTINATION include)