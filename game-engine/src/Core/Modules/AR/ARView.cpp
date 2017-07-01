#include "game-engine/Core/Modules/AR/ARView.h"

// STD
#include <vector>

// GLM
#include <glm/gtc/type_ptr.hpp>

// Game Engine
#include "game-engine/Core/Modules/Graphics/Shader.h"
#include "game-engine/Core/Modules/Graphics/Geometry.h"
#include "game-engine/Core/Modules/Graphics/Vertex.h"
#include "game-engine/Core/Modules/AR/AREntity.h"
#include "game-engine/Defines/CameraCapture.h"
#include "game-engine/Core/Engine/System.h"

const std::string ARView::SHADER_LUMA_NAME = "luma_texture";
const std::string ARView::SHADER_CHROMA_NAME = "chroma_texture";
const std::string ARView::SHADER_MODEL_NAME = "model";

const std::string ARView::SHADER_VERTEX =
"#version 300 es\n"
"\n"
"// In variables\n"
"in vec3 position;\n"
"in vec2 texCoord;\n"
"\n"
"// Out variables\n"
"out mediump vec2 TexCoord;\n"
"\n"
"// Uniform variables\n"
"uniform mat4 " + SHADER_MODEL_NAME + ";\n"
"\n"
"void main()\n"
"{\n"
"   TexCoord = texCoord;\n"
"   gl_Position = " + SHADER_MODEL_NAME + " * vec4(position, 1.0);\n"
"}\n";

const std::string ARView::SHADER_FRAGMENT =
"#version 300 es\n"
"\n"
"// In variables\n"
"in mediump vec2 TexCoord;\n"
"\n"
"// Out variables\n"
"out highp vec4 colour;\n"
"\n"
"// Uniform variables\n"
"uniform sampler2D " + SHADER_LUMA_NAME + ";\n"
"uniform sampler2D " + SHADER_CHROMA_NAME + ";\n"
"\n"
"void main()\n"
"{\n"
"   mediump vec3 yuv;\n"
"   lowp vec3 rgb;\n"
"   \n"
"   yuv.x = texture(" + SHADER_LUMA_NAME + ", TexCoord).r;\n"
"   yuv.yz = texture(" + SHADER_CHROMA_NAME + ", TexCoord).ra - vec2(0.5, 0.5);\n"
"   \n"
"   rgb = mat3( 1,       1,       1,       \n"
"               0,       -.18732, 1.8556,  \n"
"               1.57481, -.46813, 0) * yuv;\n"
"   colour = vec4(rgb, 1.0);\n"
"}\n";

ARView::ARView()
{
    
}

void ARView::initalise()
{
    unsigned int camWidth = 640, camHeight = 480;
    
    // Get min dim
    /*float min;
    if(camWidth < camHeight)
    {
        min = camWidth;
    }
    else
    {
        min = camHeight;
    }
    
    float width = min / camWidth;
    float height = min / camHeight;
    
    if(width < height)
    {
        float per = (1-width) / width;
        height += height * per;
        width = 1.0;
    }
    else
    {
        float per = (1-height) / height;
        width += width * per;
        height = 1.0;
    }*/
    float width = 1.0, height = 1.0;
    
    // Init shader
    std::vector<std::pair<GLint, std::string> > vertexAttribs;
    vertexAttribs.push_back(std::make_pair(ATTRIB_POSITION, "position"));
    vertexAttribs.push_back(std::make_pair(ATTRIB_TEXCOORD, "texCoord"));
    
    std::vector<std::string> uniformNames;
    uniformNames.push_back(SHADER_LUMA_NAME);
    uniformNames.push_back(SHADER_CHROMA_NAME);
    uniformNames.push_back(SHADER_MODEL_NAME);
    
    this->shader = Shader::loadShaderFromString(SHADER_VERTEX, SHADER_FRAGMENT, vertexAttribs, uniformNames);

    // Init geometry
    std::vector<Vertex3DPT> vertices;
    //                           | Position      | Texture |
    //                           | x     y    z  | u    v  |
    vertices.push_back(Vertex3DPT(-width, -height, 0.0, 0.0, 1.0));
    vertices.push_back(Vertex3DPT(-width,  height, 0.0, 0.0, 0.0));
    vertices.push_back(Vertex3DPT( width,  height, 0.0, 1.0, 0.0));
    vertices.push_back(Vertex3DPT( width, -height, 0.0, 1.0, 1.0));
    
    std::vector<unsigned int> indices;
    indices.push_back(0); indices.push_back(1); indices.push_back(2);
    indices.push_back(2); indices.push_back(3); indices.push_back(0);
    
    this->geometry = Geometry::loadGeometry(vertices, indices);
}

void ARView::deinitialise()
{
    //this->shader->
    //this->geometry->
}

void ARView::draw(AREntity *entity)
{
    glDisable( GL_DEPTH_TEST );
    
    shader->use();
    
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(*shader->getUniformLocation(SHADER_LUMA_NAME), 0);
    glBindTexture(GL_TEXTURE_2D, entity->getCameraCapture().getLumaTextureID());
    
    glActiveTexture(GL_TEXTURE1);
    glUniform1i(*shader->getUniformLocation(SHADER_CHROMA_NAME), 1);
    glBindTexture(GL_TEXTURE_2D, entity->getCameraCapture().getChromaTextureID());
    
    GLint *loc =shader->getUniformLocation(SHADER_MODEL_NAME);
    if(loc != NULL)
    {
        glUniformMatrix4fv(*loc, 1, false, glm::value_ptr(entity->getCameraCapture().getScale()));
    }
    
    geometry->draw();
    
    glEnable( GL_DEPTH_TEST );
}
