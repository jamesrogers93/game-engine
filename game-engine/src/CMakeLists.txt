
include(src/Core/CMakeLists.txt)
include(src/Device/CMakeLists.txt)
include(src/Entity/CMakeLists.txt)
include(src/Modules/CMakeLists.txt)
include(src/Scene/CMakeLists.txt)

list(APPEND GAME_ENGINE_SRC
	"src/JMPImporter.cpp"
	"src/GameObject.cpp"
)