#include "game-engine/Core/Modules/AR/ARView.h"

// STD
#include <vector>

// Game Engine
#include "game-engine/Core/Modules/Graphics/Shader.h"
#include "game-engine/Core/Modules/Graphics/Geometry.h"
#include "game-engine/Core/Modules/Graphics/Vertex.h"

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
"void main()\n"
"{\n"
"   TexCoord = texCoord;\n"
"   gl_Position = vec4(position, 1.0);\n"
"}\n";

const std::string ARView::SHADER_FRAGMENT =
"#version 300 es\n"
"\n"
"// In variables\n"
"in mediump vec2 TexCoord;\n"
"\n"
"// Out variables\n"
"out mediump vec4 colour;\n"
"\n"
"// Uniform variables\n"
"uniform sampler2D " + SHADER_LUMA_NAME + ";\n"
"uniform sampler2D " + SHADER_CHROMA_NAME + ";\n"
"\n"
"void main()\n"
"{\n"
"   colour = vec4(1.0, 0.0, 0.0, 1.0);\n"
"}\n";

const std::string ARView::SHADER_LUMA_NAME = "luma_texture";
const std::string ARView::SHADER_CHROMA_NAME = "chroma_texture";

ARView::ARView()
{
    
}

void ARView::initalise(const unsigned int &screenWidth, const unsigned int &screenHeight)
{
    this->width = screenWidth;
    this->height = screenHeight;
    
    // Init shader
    std::vector<std::pair<GLint, std::string> > vertexAttribs;
    vertexAttribs.push_back(std::make_pair(ATTRIB_POSITION, "position"));
    vertexAttribs.push_back(std::make_pair(ATTRIB_TEXCOORD, "texCoord"));
    
    std::vector<std::string> uniformNames;
    uniformNames.push_back(SHADER_LUMA_NAME);
    uniformNames.push_back(SHADER_CHROMA_NAME);
    
    this->shader = Shader::loadShaderFromString(SHADER_VERTEX, SHADER_FRAGMENT, vertexAttribs, uniformNames);

    // Init geometry
    std::vector<Vertex3DPT> vertices;
    //                            Position         Texture
    vertices.push_back(Vertex3DPT(-1.0, -1.0, 0.0, 0.0, 0.0));
    vertices.push_back(Vertex3DPT(-1.0,  1.0, 0.0, 0.0, 1.0));
    vertices.push_back(Vertex3DPT( 1.0,  1.0, 0.0, 1.0, 1.0));
    vertices.push_back(Vertex3DPT( 1.0, -1.0, 0.0, 1.0, 0.0));
    
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

void ARView::draw()
{
    shader->use();
    
    glUniform1i(*shader->getUniformLocation(SHADER_LUMA_NAME),   GL_TEXTURE0);
    glUniform1i(*shader->getUniformLocation(SHADER_CHROMA_NAME), GL_TEXTURE1);
    
    geometry->draw();
}
