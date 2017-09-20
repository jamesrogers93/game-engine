
include(src/Core/CMakeLists.txt)
include(src/Modules/CMakeLists.txt)
include(src/Peripherals/CMakeLists.txt)

list(APPEND GAME_ENGINE_SRC
	"src/GameObject.cpp"
)