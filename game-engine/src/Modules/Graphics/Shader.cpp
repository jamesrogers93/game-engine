#include "game-engine/Modules/Graphics/Shader.h"

// Game Engine Core
#include "game-engine/Core/GL/GL.h"

Shader::Shader()
{
	this->program = 0;
}

Shader::Shader(const GLuint program, std::map<std::string, GLint> uniforms)
{
	this->program = program;
	this->uniforms = uniforms;
}

void Shader::use()
{
	//glUseProgram(this->program);
    jmpGLUseProgram(this->program);
}

const GLuint& Shader::getProgram()
{
	return this->program;
}

/*inline const GLint* Shader::getUniformLocation(const std::string &name) const
{
    //if (this->uniforms.find(name) != this->uniforms.end())
    //{
    //    return &this->uniforms[name];
    //}
    
    return &this->uniforms.at(name);
    
    //return NULL;
}*/

Shader* Shader::loadShaderFromFile(const std::string &vertexPath, const std::string &fragmentPath, std::vector<std::pair<GLint, std::string> > vertexAttribs, std::vector<std::string> uniformNames)
{
    std::string vertexCode, fragmentCode;
    std::ifstream vShaderFile, fShaderFile;
    
    //For throwing exceptions
    vShaderFile.exceptions(std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::badbit);
    
    //try
    //{
    //Open the files.
    vShaderFile.open(vertexPath.c_str());
    fShaderFile.open(fragmentPath.c_str());
    
    std::stringstream vShaderStream, fShaderStream;
    
    //Read buffer contents in to streams.
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();
    
    //Close files.
    vShaderFile.close();
    fShaderFile.close();
    
    //Convert stream to string
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
    //}
    //catch (std::ifstream::failure e)
    //{
    //	std::cout << "ERROR, shader file could not be read" << std::endl;
    //	return NULL;
    //}
    
    return loadShaderFromString(vertexCode, fragmentCode, vertexAttribs, uniformNames);
}

Shader* Shader::loadShaderFromString(const std::string &vertex, const std::string &fragment, std::vector<std::pair<GLint, std::string> > vertexAttribs, std::vector<std::string> uniformNames)
{
	GLuint program = 0;
	GLuint vertShader = 0;
	GLuint fragShader = 0;

    std::string vertexCode = vertex;
    std::string fragmentCode = fragment;
    
	// Create shader program
	program = glCreateProgram();

	if (!compileShader(&vertShader, GL_VERTEX_SHADER, &vertexCode))
	{
		return NULL;
	}

	if (!compileShader(&fragShader, GL_FRAGMENT_SHADER, &fragmentCode))
	{
		return NULL;
	}

	//Link Shaders to program
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);

	// Bind attribute locations.
	// This needs to be done prior to linking.

	for (std::vector<std::pair<GLint, std::string> >::iterator it = vertexAttribs.begin(); it != vertexAttribs.end(); ++it)
	{
		glBindAttribLocation(program, it->first, it->second.c_str());
	}


	if (!linkProgram(&program))
	{
		
		if (vertShader != 0)
		{
			glDeleteShader(vertShader);
			vertShader = 0;
		}

		if (fragShader != 0)
		{
			glDeleteShader(fragShader);
			fragShader = 0;
		}
		if (program != 0)
		{
			glDeleteProgram(program);
			program = 0;
		}

		std::cout << "Failed to link program: \(program)" << std::endl;
		return NULL;
	}

	// Get uniform locations.
	std::map<std::string, GLint> uniforms;
	for (std::vector<std::string>::iterator it = uniformNames.begin(); it != uniformNames.end(); ++it)
	{
		uniforms[*it] = glGetUniformLocation(program, it->c_str());
	}

	//Now shaders are loaded into program, delete them
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	return new Shader(program, uniforms);
}


bool Shader::compileShader(GLuint *shader, const int &type, std::string *file)
{

	/*if (type != GL_VERTEX_SHADER || type != GL_FRAGMENT_SHADER)
	{
		std::cout << "Incorrect Shader Type" << std::endl;
        
        std::cout << type << std::endl;
        std::cout << GL_VERTEX_SHADER << std::endl;
		return false;
	}*/

	GLint success;
	GLchar infoLog[512];
	const GLchar* source;

	//Copy vertex and fragment code to GLchar*'s
	source = file->c_str();

	//Vertex Shader
	*shader = glCreateShader(type);
	glShaderSource(*shader, 1, &source, NULL);
	glCompileShader(*shader);

	//Check for errors
	glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(*shader, 512, NULL, infoLog);
		std::cout << "Shader compilation failed " << infoLog << std::endl;
		glDeleteShader(*shader);
		return false;
	}

	return true;
}

bool Shader::linkProgram(GLuint *program)
{
	GLint status = 0;
	GLchar infoLog[512];

	glLinkProgram(*program);

	//Check for errors
	glGetProgramiv(*program, GL_LINK_STATUS, &status);
	if (!status)
	{
		glGetProgramInfoLog(*program, 512, NULL, infoLog);
		std::cout << "Shader program compilation failed " << infoLog << std::endl;
	
		return false;
	}

	return true;
}
