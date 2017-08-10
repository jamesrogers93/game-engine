
include(src/Modules/Animation/CMakeLists.txt)
include(src/Modules/Graphics/CMakeLists.txt)
include(src/Modules/GUI/CMakeLists.txt)
# AR only supported on IOS 
if(IOS)
	include(src/Modules/AR/CMakeLists.txt)
endif()

list(APPEND GAME_ENGINE_SRC
	"src/Modules/CoreModule.cpp"
)