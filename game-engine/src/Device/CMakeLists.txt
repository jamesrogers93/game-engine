
list(APPEND GAME_ENGINE_SRC
	"src/Device/CameraCapture.cpp"
    "src/Device/Gyroscope.cpp"
    "src/Device/System.cpp"
    
)

if(IOS)
    list(APPEND GAME_ENGINE_SRC
	    "src/Device/CameraCapture-iOS.mm"
        "src/Device/Gyroscope-iOS.mm"
    )
endif()