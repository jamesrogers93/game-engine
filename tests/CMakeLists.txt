
add_executable (GameEngineTest main.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../game-engine/include)

target_link_libraries (GameEngineTest GameEngine)

