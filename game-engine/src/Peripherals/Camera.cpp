
// Game Engine Device
#include "game-engine/Peripherals/Camera.h"
#include "game-engine/Peripherals/System.h"

// STD
#include <vector>

// GLM
#include <glm/gtc/type_ptr.hpp>

// Game Engine Core
#include "game-engine/Core/GL/GLThread.h"

// Game Engine Graphics
#include "game-engine/Modules/Graphics/Shader.h"
#include "game-engine/Modules/Graphics/Mesh.h"
#include "game-engine/Modules/Graphics/Vertex.h"

const Camera::Resolution Camera::DEFAULT_RES = RES_NOT_SET;

const std::string Camera::SHADER_LUMA_NAME = "luma_texture";
const std::string Camera::SHADER_CHROMA_NAME = "chroma_texture";
const std::string Camera::SHADER_MODEL_NAME = "model";

const std::string Camera::SHADER_VERTEX =
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

const std::string Camera::SHADER_FRAGMENT =
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

Camera::Camera() : res(DEFAULT_RES), initialised(false), capturing(false)
{
    delegateDispatchQueue.initialise("camera_capture");

}

Camera::~Camera()
{
    
}

void Camera::display()
{
    if(capturing)
    {
        glDisable( GL_DEPTH_TEST );
        
        shader->use();
        
        glActiveTexture(GL_TEXTURE0);
        
        glUniform1i(*shader->getUniformLocation(SHADER_LUMA_NAME), 0);
        glBindTexture(GL_TEXTURE_2D, this->getLumaTextureID());
        
        glActiveTexture(GL_TEXTURE1);
        
        glUniform1i(*shader->getUniformLocation(SHADER_CHROMA_NAME), 1);
        glBindTexture(GL_TEXTURE_2D, this->getChromaTextureID());
        
        const GLint *loc = shader->getUniformLocation(SHADER_MODEL_NAME);
        //if(loc != NULL)
        //{
        glUniformMatrix4fv(*loc, 1, false, glm::value_ptr(this->getScale()));
        //}
        
        geometry->draw(GL_TRIANGLES);
        
        glEnable( GL_DEPTH_TEST );
    }
}

bool Camera::initialise()
{
    if(this->initialised)
    {
        return false;
    }
    
    if(this->res == RES_NOT_SET)
    {
        return false;
    }
    
    bool status = initialiseCamera();
    
    if(status)
    {
        unsigned int screenWidth = System::screenWidth;
        unsigned int screenHeight = System::screenHeight;
        
        // Check if aspect ratio of camera image is different from screen
        float cameraAspectRatio = (float)cameraWidth / (float)cameraHeight;
        float screenAspectRatio = (float)screenWidth / (float)screenHeight;
        if( cameraAspectRatio != screenAspectRatio)
        {
            
            // Scale camera so that it's entire image fits the screen
            float heightScale = (float)screenHeight / (float)cameraHeight;
            float widthScale = (float)screenWidth / (float)cameraWidth;
            
            float w = 1.0, h = 1.0;
            if(widthScale < heightScale)
            {
                float width = (float)cameraWidth * heightScale;
                w = width / (float)screenWidth;
            }
            else
            {
                float height = (float)cameraHeight * widthScale;
                h = height / (float)screenHeight;
            }
            
            this->scale = glm::scale(glm::mat4(), glm::vec3(w, h, 1.0));
        }
        
    }
    
    initialiseView();
    
    return status;
}

void Camera::initialiseView()
{
    float width = 1.0, height = 1.0;
    
    // Init shader
    std::vector<std::pair<GLint, std::string> > vertexAttribs;
    vertexAttribs.push_back(std::make_pair(ATTRIB_POSITION, "position"));
    vertexAttribs.push_back(std::make_pair(ATTRIB_UV0, "texCoord"));
    
    std::vector<std::string> uniformNames;
    uniformNames.push_back(SHADER_LUMA_NAME);
    uniformNames.push_back(SHADER_CHROMA_NAME);
    uniformNames.push_back(SHADER_MODEL_NAME);
    
    this->shader = Shader::loadShaderFromString(SHADER_VERTEX, SHADER_FRAGMENT, vertexAttribs, uniformNames);
    
    // Init geometry
    std::vector<VertexPU> vertices;
    VertexPU v1,v2,v3,v4;
    v1.position = glm::vec3(-width, -height, 0.0);
    v2.position = glm::vec3(-width,  height, 0.0);
    v3.position = glm::vec3( width,  height, 0.0);
    v4.position = glm::vec3( width, -height, 0.0);
    
    v1.uv0 = glm::vec2(0.0, 1.0);
    v2.uv0 = glm::vec2(0.0, 0.0);
    v3.uv0 = glm::vec2(1.0, 0.0);
    v4.uv0 = glm::vec2(1.0, 1.0);
    
    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);
    vertices.push_back(v4);
    
    
    /*std::vector<Vertex3DPT> vertices;
     //                           | Position           | Texture |
     //                           | x       y       z  | u    v  |
     vertices.push_back(Vertex3DPT(-width, -height, 0.0, 0.0, 1.0));
     vertices.push_back(Vertex3DPT(-width,  height, 0.0, 0.0, 0.0));
     vertices.push_back(Vertex3DPT( width,  height, 0.0, 1.0, 0.0));
     vertices.push_back(Vertex3DPT( width, -height, 0.0, 1.0, 1.0));*/
    
    std::vector<unsigned int> indices;
    indices.push_back(0); indices.push_back(1); indices.push_back(2);
    indices.push_back(2); indices.push_back(3); indices.push_back(0);
    
    this->geometry = MeshGL::loadMeshGL(vertices, indices);
}

void Camera::addDelegate(CameraCaptureDelegate* delegate)
{
    this->delegates.push_back(delegate);
}

void Camera::removeDelegate(CameraCaptureDelegate* delegate)
{
    for(auto it = delegates.begin(); it != delegates.end(); )
    {
        if((*it) == delegate)
        {
            it = delegates.erase(it);
        }
    }
}

void Camera::callDelegates(unsigned char *data, const float &width, const float &height, const float &padding)
{
    for(unsigned int i = 0; i < this->delegates.size(); i++)
    {
        if(delegates[i] != NULL)
        {
            std::function<void()> frameRecievedFunc = std::bind(&CameraCaptureDelegate::frameRecieved,
                                                                this->delegates[i],
                                                                data, width, height, padding);
            Task myTask = Task(frameRecievedFunc);
            //delegateDispatchQueue.sendToQueue(myTask);
            
            this->delegates[i]->frameRecieved(data, width, height, padding);
        }
    }
}

