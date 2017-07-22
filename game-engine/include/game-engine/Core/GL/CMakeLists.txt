
list(APPEND GAME_ENGINE_INC
"include/game-engine/Core/GL/GL.h"
    "include/game-engine/Core/GL/GLContext.h"
)

if(IOS)
    list(APPEND GAME_ENGINE_INC
        "include/game-engine/Core/GL/GLContext-iOS.h"
    )
endif()