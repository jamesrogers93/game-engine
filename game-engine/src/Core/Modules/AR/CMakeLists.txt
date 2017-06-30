
list(APPEND GAME_ENGINE_SRC
	"src/Core/Modules/AR/AR.cpp"
    "src/Core/Modules/AR/AREntity.cpp"
    "src/Core/Modules/AR/ARView.cpp"
)

if(IOS)
    list(APPEND GAME_ENGINE_SRC
	    "src/Core/Modules/AR/CameraCapture-iOS.mm"
    )
endif()