
list(APPEND GAME_ENGINE_SRC
    "src/Core/GL/GLContext.cpp" 
)

if(IOS)
    list(APPEND GAME_ENGINE_SRC
        "src/Core/GL/GLContext-iOS.mm"
    )
endif()