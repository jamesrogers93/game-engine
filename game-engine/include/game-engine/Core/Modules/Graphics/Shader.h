#ifndef _SHADER_H
#define _SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>
#include <vector>
#include <map>

// Game Engine Defines
#include "game-engine/Defines/OpenGL.h"

class Shader
{
private:
	GLuint program;
	std::map<std::string, GLint> uniforms;

	Shader();
	Shader(const GLuint program, std::map<std::string, GLint> uniforms);

	static bool compileShader(GLuint *shader, const int &type, std::string *file);
	static bool linkProgram(GLuint *program);

public:

	const GLuint& getProgram();
    GLint* getUniformLocation(const std::string &name);

	void use();
	static Shader* loadShaderFromFile(const std::string &vertexPath, const std::string &fragmentPath, std::vector<std::pair<GLint, std::string> > vertexAttribs, std::vector<std::string> uniformNames);
    
    static Shader* loadShaderFromString(const std::string &vertex, const std::string &fragment, std::vector<std::pair<GLint, std::string> > vertexAttribs, std::vector<std::string> uniformNames);
};

const GLuint ATTRIB_POSITION = 0;
const GLuint ATTRIB_NORMAL = 1;
const GLuint ATTRIB_UV0 = 2;
const GLuint ATTRIB_COLOUR = 3;

#endif /* _SHADER_H */
