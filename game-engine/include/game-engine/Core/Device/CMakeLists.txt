list(APPEND GAME_ENGINE_INC
    "include/game-engine/Core/Device/CameraCapture.h"
    "include/game-engine/Core/Device/GLContext.h"
    "include/game-engine/Core/Device/Gyroscope.h"
    "include/game-engine/Core/Device/System.h"
)

if(IOS)
    list(APPEND GAME_ENGINE_INC
	    "include/game-engine/Core/Device/CameraCapture-iOS.h"
        "include/game-engine/Core/Device/GLContext-iOS.h"
        "include/game-engine/Core/Device/Gyroscope-iOS.h"
    )
endif()