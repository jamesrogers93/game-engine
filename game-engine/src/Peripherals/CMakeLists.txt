
list(APPEND GAME_ENGINE_SRC
    "src/Peripherals/Camera.cpp"
    "src/Peripherals/CameraAbstract.cpp"
    "src/Peripherals/CameraAbstractFactory.cpp"
    "src/Peripherals/CameraCapture.cpp"
    "src/Peripherals/CameraIOSFactory.cpp"
    "src/Peripherals/Gyroscope.cpp"
    "src/Peripherals/System.cpp"
    
)

if(IOS)
    list(APPEND GAME_ENGINE_SRC
	    "src/Peripherals/CameraCapture-iOS.mm"
        "src/Peripherals/Gyroscope-iOS.mm"
    )
endif()