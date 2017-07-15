list(APPEND GAME_ENGINE_INC
    "include/game-engine/Device/CameraCapture.h"
    "include/game-engine/Device/Gyroscope.h"
    "include/game-engine/Device/System.h"
)

if(IOS)
    list(APPEND GAME_ENGINE_INC
	    "include/game-engine/Device/CameraCapture-iOS.h"
        "include/game-engine/Device/Gyroscope-iOS.h"
    )
endif()