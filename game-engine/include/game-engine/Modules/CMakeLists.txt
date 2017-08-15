
include(include/game-engine/Modules/Animation/CMakeLists.txt)
include(include/game-engine/Modules/Graphics/CMakeLists.txt)
include(include/game-engine/Modules/GUI/CMakeLists.txt)
include(include/game-engine/Modules/Physics/CMakeLists.txt)

# AR only supported on IOS 
if(IOS)
	include(include/game-engine/Modules/AR/CMakeLists.txt)
endif()

list(APPEND GAME_ENGINE_INC
	"include/game-engine/Modules/CoreModule.h"
)