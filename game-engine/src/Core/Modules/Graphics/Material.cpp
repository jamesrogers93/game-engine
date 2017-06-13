
// Game Engine Core
#include "game-engine/Core/Modules/Graphics/Material.h"
#include "game-engine/Core/Modules/Graphics/Graphics.h"
#include "game-engine/Core/Modules/Graphics/Shader.h"
#include "game-engine/Core/Modules/Graphics/Texture.h"

// Game Engine Defines
#include "game-engine/Defines/OpenGL.h"

// GLM
#include <glm/gtc/type_ptr.hpp>

const float Material::SHININESS_DEFAULT = 1.0;

bool Material::loadToShader(Shader *shader)
{
    //Shader *shader = Graphics::getInstance().getShader(this->shaderName);
    if(shader == NULL)
    {
        return false;
    }
    
    if(this->isDiffuseTexture)
    {
        GLint *loc = shader->getUniformLocation("diffuseTexture");
        if(loc != NULL)
        {
            Texture *tex = Graphics::getInstance().getTexture("");
            
            if(tex != NULL)
            {
                glActiveTexture(GL_TEXTURE0);
                glUniform1f(*loc, 0);
                glBindTexture(GL_TEXTURE_2D, tex->getTextureID());
            }
        }
    }
    
    if(this->isSpecularTexture)
    {
        GLint *loc = shader->getUniformLocation("specularTexture");
        if(loc != NULL)
        {
            Texture *tex = Graphics::getInstance().getTexture("");
            
            if(tex != NULL)
            {
                glActiveTexture(GL_TEXTURE1);
                glUniform1f(*loc, 1);
                glBindTexture(GL_TEXTURE_2D, tex->getTextureID());
            }
        }
    }
    
    if(this->isDiffuseSolid)
    {
        GLint *loc = shader->getUniformLocation("diffuseSolid");
        if(loc != NULL)
        {
            glUniform4fv(*loc, 1, glm::value_ptr(this->diffuseSolid));
        }
    }
    
    if(this->isSpecularSolid)
    {
        GLint *loc = shader->getUniformLocation("specularSolid");
        if(loc != NULL)
        {
            glUniform4fv(*loc, 1, glm::value_ptr(this->specularSolid));
        }
    }
    
    GLint *shininess = shader->getUniformLocation("shininess");
    if(shininess != NULL)
    {
        glUniform1f(*shininess, this->shininess);
    }
    
    return true;
}
