
# AR only supported on IOS 
if(IOS)
	include(include/game-engine/Modules/AR/CMakeLists.txt)
endif()

include(include/game-engine/Modules/Graphics/CMakeLists.txt)

list(APPEND GAME_ENGINE_INC
	"include/game-engine/Modules/CoreModule.h"
)