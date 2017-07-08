
# AR only supported on IOS 
if(IOS)
	include(src/Core/Modules/AR/CMakeLists.txt)
endif()

include(src/Core/Modules/Graphics/CMakeLists.txt)

list(APPEND GAME_ENGINE_SRC
	"src/Core/Modules/CoreModule.cpp"
)