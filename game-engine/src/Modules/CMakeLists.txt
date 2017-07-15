
# AR only supported on IOS 
if(IOS)
	include(src/Modules/AR/CMakeLists.txt)
endif()

include(src/Modules/Graphics/CMakeLists.txt)

list(APPEND GAME_ENGINE_SRC
	"src/Modules/CoreModule.cpp"
)