
include(src/Core/Modules/AR/CMakeLists.txt)
include(src/Core/Modules/Graphics/CMakeLists.txt)

list(APPEND GAME_ENGINE_SRC
	"src/Core/Modules/CoreModule.cpp"
)