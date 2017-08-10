#ifndef _SHADER_H
#define _SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>
#include <vector>
#include <unordered_map>

// Game Engine Defines
#include "game-engine/Defines/OpenGL.h"

struct ShaderFlag {
    bool flag = true;
};

class Shader
{
private:
	GLuint program;
	std::unordered_map<std::string, GLint> uniforms;

	Shader();
	Shader(const GLuint program, std::unordered_map<std::string, GLint> uniforms);

	static bool compileShader(GLuint *shader, const int &type, std::string *file);
	static bool linkProgram(GLuint *program);

public:

	const GLuint& getProgram();
    inline const GLint* getUniformLocation(const std::string &name) const
    {
        auto it = uniforms.find(name);
        
        if(it != uniforms.end())
        {
            return &it->second;
            //return &this->uniforms.at(name);
        }
        else
        {
            // Log
            std::cout << "Uniform: " << name << " does not exist in shader" << std::endl;;
            return NULL;
        }
    }

	void use();
	static Shader* loadShaderFromFile(const std::string &vertexPath, const std::string &fragmentPath, std::vector<std::pair<GLint, std::string> > vertexAttribs, std::vector<std::string> uniformNames);
    
    static Shader* loadShaderFromString(const std::string &vertex, const std::string &fragment, std::vector<std::pair<GLint, std::string> > vertexAttribs, std::vector<std::string> uniformNames);
};

const GLuint ATTRIB_POSITION = 0;
const GLuint ATTRIB_NORMAL = 1;
const GLuint ATTRIB_UV0 = 2;
const GLuint ATTRIB_COLOUR = 3;
const GLuint ATTRIB_JOINT_ID = 4;
const GLuint ATTRIB_JOINT_WEIGHT = 5;

#endif /* _SHADER_H */
