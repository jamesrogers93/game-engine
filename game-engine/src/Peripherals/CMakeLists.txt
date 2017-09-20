
list(APPEND GAME_ENGINE_SRC
	"src/Peripherals/CameraCapture.cpp"
    "src/Peripherals/Gyroscope.cpp"
    "src/Peripherals/System.cpp"
    
)

if(IOS)
    list(APPEND GAME_ENGINE_SRC
	    "src/Peripherals/CameraCapture-iOS.mm"
        "src/Peripherals/Gyroscope-iOS.mm"
    )
endif()