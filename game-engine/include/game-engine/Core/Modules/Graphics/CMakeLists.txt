list(APPEND GAME_ENGINE_INC
	"include/game-engine/Core/Modules/Graphics/CameraEntity.h"
	"include/game-engine/Core/Modules/Graphics/Context.h"
	"include/game-engine/Core/Modules/Graphics/CameraEntity.h"
	"include/game-engine/Core/Modules/Graphics/DirectionalLightEntity.h"
	"include/game-engine/Core/Modules/Graphics/Geometry.h"
	"include/game-engine/Core/Modules/Graphics/GeometryEntity.h"
	"include/game-engine/Core/Modules/Graphics/Graphics.h"
	"include/game-engine/Core/Modules/Graphics/GraphicsRead.h"
	"include/game-engine/Core/Modules/Graphics/LightEntity.h"
	"include/game-engine/Core/Modules/Graphics/Material.h"
	"include/game-engine/Core/Modules/Graphics/PointLightEntity.h"
	"include/game-engine/Core/Modules/Graphics/Shader.h"
	"include/game-engine/Core/Modules/Graphics/Shaders.h"
	"include/game-engine/Core/Modules/Graphics/Texture.h"
	"include/game-engine/Core/Modules/Graphics/Vertex.h"
)

if(IOS)
	list(APPEND GAME_ENGINE_INC
		"include/game-engine/Core/Modules/Graphics/Context-iOS.h"
	)
endif()
