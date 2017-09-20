
list(APPEND GAME_ENGINE_INC
    "include/game-engine/Core/GL/GL.h"
    "include/game-engine/Core/GL/GLContext.h"
    "include/game-engine/Core/GL/GLData.h"
    "include/game-engine/Core/GL/GLSharegroup.h"
    "include/game-engine/Core/GL/GLTexture.h"
    "include/game-engine/Core/GL/GLThread.h"
    "include/game-engine/Core/GL/OpenGL.h"
)

if(IOS)
    list(APPEND GAME_ENGINE_INC
        "include/game-engine/Core/GL/GLContext-iOS.h"
        "include/game-engine/Core/GL/GLSharegroup-iOS.h"
    )
endif()