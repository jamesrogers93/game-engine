list(APPEND GAME_ENGINE_INC
    "include/game-engine/Peripherals/Camera.h"
    "include/game-engine/Peripherals/CameraAbstract.h"
    "include/game-engine/Peripherals/CameraAbstractFactory.h"
    "include/game-engine/Peripherals/CameraCapture.h"
    "include/game-engine/Peripherals/CameraIOSFactory.h"
    "include/game-engine/Peripherals/Gyroscope.h"
    "include/game-engine/Peripherals/System.h"
)

if(IOS)
    list(APPEND GAME_ENGINE_INC
	    "include/game-engine/Peripherals/CameraCapture-iOS.h"
        "include/game-engine/Peripherals/Gyroscope-iOS.h"
    )
endif()