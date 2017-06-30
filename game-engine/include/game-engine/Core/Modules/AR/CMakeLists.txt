
list(APPEND GAME_ENGINE_INC
	"include/game-engine/Core/Modules/AR/AR.h"
    "include/game-engine/Core/Modules/AR/AREntity.h"
    "include/game-engine/Core/Modules/AR/ARView.h"
)

if(IOS)
    list(APPEND GAME_ENGINE_INC
        "include/game-engine/Core/Modules/AR/CameraCaptureInterface-iOS.h"
	    "include/game-engine/Core/Modules/AR/CameraCapture-iOS.h"
    )
endif()