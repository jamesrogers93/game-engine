
# AR only supported on IOS 
if(IOS)
	include(include/game-engine/Core/Modules/AR/CMakeLists.txt)
endif()

include(include/game-engine/Core/Modules/Graphics/CMakeLists.txt)

list(APPEND GAME_ENGINE_INC
	"include/game-engine/Core/Modules/CoreModule.h"
)