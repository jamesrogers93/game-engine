
list(APPEND GAME_ENGINE_SRC
	"src/Core/Device/CameraCapture.cpp"
    "src/Core/Device/GLContext.cpp"
    "src/Core/Device/Gyroscope.cpp"
    "src/Core/Device/System.cpp"
    
)

if(IOS)
    list(APPEND GAME_ENGINE_SRC
	    "src/Core/Device/CameraCapture-iOS.mm"
        "src/Core/Device/GLContext-iOS.mm"
        "src/Core/Device/Gyroscope-iOS.mm"
    )
endif()