#ifndef _SHADER_H
#define _SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>
#include <vector>
#include <map>

#include "game-engine/Defines/OpenGL.h"

class Shader
{
private:
	GLuint program;
	std::map<std::string, GLint> uniforms;

	Shader();
	Shader(const GLuint program, std::map<std::string, GLint> uniforms);

	static bool compileShader(GLuint *shader, const int type, std::string *file);
	static bool linkProgram(GLuint *program);

public:

	const GLuint& getProgram();

	void use();
	static Shader* loadShader(const std::string *vertex, const std::string *fragment, std::vector<std::pair<GLint, std::string> > vertexAttribs, std::vector<std::string> uniformNames);
};

const GLuint POSITION_ATTRIB = 0;
const GLuint NORMAL_ATTRIB = 0;
const GLuint TEXCOORD_ATTRIB = 0;

#endif /* _SHADER_H */
