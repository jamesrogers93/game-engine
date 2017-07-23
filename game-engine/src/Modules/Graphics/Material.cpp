
// Game Engine Graphics
#include "game-engine/Modules/Graphics/Material.h"
#include "game-engine/Modules/Graphics/Graphics.h"
#include "game-engine/Modules/Graphics/Shader.h"
#include "game-engine/Modules/Graphics/Texture.h"

// Game Engine Core
#include "game-engine/Core/GL/GL.h"

// Game Engine Defines
#include "game-engine/Defines/OpenGL.h"

// GLM
#include <glm/gtc/type_ptr.hpp>

const float Material::SHININESS_DEFAULT = 16.0;

const std::string Material::SHADER_DIFF_TEX_NAME = "material.diffuseMap";
const std::string Material::SHADER_SPEC_TEX_NAME = "material.specularMap";
const std::string Material::SHADER_DIFF_SOLID_NAME = "material.diffuse";
const std::string Material::SHADER_SPEC_SOLID_NAME = "material.specular";
const std::string Material::SHADER_SHININESS_NAME = "material.shininess";

bool Material::loadToShader(Shader *shader)
{
    //Shader *shader = Graphics::getInstance().getShader(this->shaderName);
    if(shader == NULL)
    {
        return false;
    }
    
    /*if(this->isDiffuseTexture)
    {
        GLint *loc = shader->getUniformLocation(SHADER_DIFF_TEX_NAME);
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
        GLint *loc = shader->getUniformLocation(SHADER_SPEC_TEX_NAME);
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
    }*/
    
    //if(this->isDiffuseSolid)
    //{
        const GLint *loc = shader->getUniformLocation(SHADER_DIFF_SOLID_NAME);
        //if(loc != NULL)
        //{
            glUniform4fv(*loc, 1, glm::value_ptr(this->diffuseSolid));
            //jmpGLUniform4fv(shader->getProgram(), *loc, 1, glm::value_ptr(this->diffuseSolid));
        //}
    //}
    
    //if(this->isSpecularSolid)
    //{
        loc = shader->getUniformLocation(SHADER_SPEC_SOLID_NAME);
        //if(loc != NULL)
        //{
            glUniform4fv(*loc, 1, glm::value_ptr(this->specularSolid));
            //jmpGLUniform4fv(shader->getProgram(), *loc, 1, glm::value_ptr(this->specularSolid));
        //}
    //}
    
    loc = shader->getUniformLocation(SHADER_SHININESS_NAME);
    //if(shininess != NULL)
    //{
        glUniform1f(*loc, this->shininess);
        //jmpGLUniform1f(shader->getProgram(), *loc, this->shininess);
    //}
    
    return true;
}


void Material::fillUniformNames(std::vector<std::string> &uniformNames)
{
    uniformNames.push_back(SHADER_DIFF_TEX_NAME);
    uniformNames.push_back(SHADER_SPEC_TEX_NAME);
    uniformNames.push_back(SHADER_DIFF_SOLID_NAME);
    uniformNames.push_back(SHADER_SPEC_SOLID_NAME);
    uniformNames.push_back(SHADER_SHININESS_NAME);
}

