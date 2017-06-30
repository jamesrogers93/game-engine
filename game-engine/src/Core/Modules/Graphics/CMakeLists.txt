
list(APPEND GAME_ENGINE_SRC
	"src/Core/Modules/Graphics/CameraEntity.cpp"
	"src/Core/Modules/Graphics/DirectionalLightEntity.cpp"
	"src/Core/Modules/Graphics/Geometry.cpp"
	"src/Core/Modules/Graphics/GeometryEntity.cpp"
	"src/Core/Modules/Graphics/Graphics.cpp"
	"src/Core/Modules/Graphics/GraphicsRead.cpp"
	"src/Core/Modules/Graphics/LightEntity.cpp"
	"src/Core/Modules/Graphics/Material.cpp"
	"src/Core/Modules/Graphics/PointLightEntity.cpp"
	"src/Core/Modules/Graphics/Shader.cpp"
	"src/Core/Modules/Graphics/Texture.cpp"
)

if(IOS)
	list(APPEND GAME_ENGINE_SRC
		"src/Core/Modules/Graphics/Context-iOS.mm"
	)
endif()
