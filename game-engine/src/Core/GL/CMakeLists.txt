
list(APPEND GAME_ENGINE_SRC
    "src/Core/GL/GL.cpp" 
    "src/Core/GL/GLContext.cpp" 
    "src/Core/GL/GLSharegroup.cpp" 
    "src/Core/GL/GLTexture.cpp" 
)

if(IOS)
    list(APPEND GAME_ENGINE_SRC
        "src/Core/GL/GLContext-iOS.mm"
        "src/Core/GL/GLSharegroup-iOS.mm"
    )
endif()