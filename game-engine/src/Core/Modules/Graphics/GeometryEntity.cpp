#include "game-engine/Core/Modules/Graphics/GeometryEntity.h"

// GLM
#include <glm/gtc/type_ptr.hpp>

// Game Engine Core
#include "game-engine/Core/Modules/Graphics/Graphics.h"
#include "game-engine/Core/Modules/Graphics/Shader.h"

// Game Engine Defines
#include "game-engine/Defines/OpenGL.h"

void GeometryEntity::attachToEngine()
{
    Graphics *g = &Graphics::getInstance();
    
    g->addGeometryEntity(this->name, this);
}

void GeometryEntity::loadToShader(Shader *shader)
{
    // Load projection to shader
    glUniformMatrix4fv(*shader->getUniformLocation("model"), 1, false, glm::value_ptr(this->globalModel));
    
}
