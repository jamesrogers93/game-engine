#ifndef _GL_H
#define _GL_H

#include "game-engine/Defines/OpenGL.h"

#include "game-engine/Core/GL/GLData.h"

#include <utility>
#include <map>
#include <cfloat>
#include <cmath>

struct UniformMatrix4fv
{
    GLint location;
    GLsizei count;
    GLfloat m00, m01, m02, m03;
    GLfloat m10, m11, m12, m13;
    GLfloat m20, m21, m22, m23;
    GLfloat m30, m31, m32, m33;
};

struct UniformMatrix3fv
{
    GLint location;
    GLsizei count;
    GLfloat m00, m01, m02;
    GLfloat m10, m11, m12;
    GLfloat m20, m21, m22;
};

struct Uniform3fv
{
    GLint location;
    GLsizei count;
    GLfloat x, y, z;
};

struct Uniform4fv
{
    GLint location;
    GLsizei count;
    GLfloat x, y, z, w;
};

struct Uniform1i
{
    GLint location;
    GLint x;
};

struct Uniform1f
{
    GLint location;
    GLfloat x;
};

inline void jmpGLClearColour(const float &r, const float &g, const float &b, const float &a)
{
    static float sr = 0.0;
    static float sg = 0.0;
    static float sb = 0.0;
    static float sa = 0.0;
    
    
    if ((sr == r) && (sg == g) && (sb == b) && (sa == a))
    {
        return;
    }
    
    sr = r;
    sg = g;
    sb = b;
    sa = a;
    
    glClearColor(sr, sg, sb, sa);
}

inline void jmpGLTexParameterf(const GLenum &target, const GLenum &pname, const GLfloat &param)
{
    if(target == GL_TEXTURE_2D && pname == GL_TEXTURE_WRAP_S)
    {
        static GLfloat sParam = 0.0;
        
        if(sParam == param)
        {
            return;
        }
        
        sParam = param;
        
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sParam);
    }
    
    if(target == GL_TEXTURE_2D && pname == GL_TEXTURE_WRAP_T)
    {
        static GLfloat sParam = 0.0;
        
        if(sParam == param)
        {
            return;
        }
        
        sParam = param;
        
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, sParam);
    }
}

inline void jmpGLUseProgram (const GLuint &program)
{
    static GLuint sProgram = 0;
    
    if(sProgram == program)
    {
        return;
    }
    
    sProgram = program;
    
    glUseProgram(sProgram);
}

//void jmpGLUniformMatrix4fv(const UpdateNotification &updateNotification, const GLuint &programId, const GLint &location, const GLsizei &count, const bool &transpose, const GLfloat* m)
inline void jmpGLUniformMatrix4fv(const GLuint &programId, const GLint &location, const GLsizei &count, const bool &transpose, const GLfloat* m)
{
    
    /*static std::map<std::pair<GLuint, GLint>, UpdateNotification> update;
    
    if(update[std::make_pair(programId, location)].getFlag() == updateNotification.getFlag())
    {
        return;
    }
    
    update[std::make_pair(programId, location)].notify();*/
    
    glUniformMatrix4fv(location, count, transpose, m);
    return;
    
    static std::map<std::pair<GLuint, GLint> , UniformMatrix4fv> uniformMatrix4fvs;
    
    UniformMatrix4fv *uniformMatrix4fv = &uniformMatrix4fvs[std::make_pair(programId, location)];
    if(uniformMatrix4fv->location == location
       && uniformMatrix4fv->count == count
       && fabs(uniformMatrix4fv->m00 -  m[0]) < FLT_EPSILON
       && fabs(uniformMatrix4fv->m01 -  m[1]) < FLT_EPSILON
       && fabs(uniformMatrix4fv->m02 -  m[2]) < FLT_EPSILON
       && fabs(uniformMatrix4fv->m03 -  m[3]) < FLT_EPSILON

       && fabs(uniformMatrix4fv->m10 -  m[4]) < FLT_EPSILON
       && fabs(uniformMatrix4fv->m11 -  m[5]) < FLT_EPSILON
       && fabs(uniformMatrix4fv->m12 -  m[6]) < FLT_EPSILON
       && fabs(uniformMatrix4fv->m13 -  m[7]) < FLT_EPSILON

       && fabs(uniformMatrix4fv->m20 -  m[8]) < FLT_EPSILON
       && fabs(uniformMatrix4fv->m21 -  m[9]) < FLT_EPSILON
       && fabs(uniformMatrix4fv->m22 - m[10]) < FLT_EPSILON
       && fabs(uniformMatrix4fv->m23 - m[11]) < FLT_EPSILON

       && fabs(uniformMatrix4fv->m30 - m[12]) < FLT_EPSILON
       && fabs(uniformMatrix4fv->m31 - m[13]) < FLT_EPSILON
       && fabs(uniformMatrix4fv->m32 - m[14]) < FLT_EPSILON
       && fabs(uniformMatrix4fv->m33 - m[15]) < FLT_EPSILON)
    {
        return;
    }
    
    uniformMatrix4fv->location = location;
    uniformMatrix4fv->count = count;
    uniformMatrix4fv->m00 = m[0];
    uniformMatrix4fv->m01 = m[1];
    uniformMatrix4fv->m02 = m[2];
    uniformMatrix4fv->m03 = m[3];

    uniformMatrix4fv->m10 = m[4];
    uniformMatrix4fv->m11 = m[5];
    uniformMatrix4fv->m12 = m[6];
    uniformMatrix4fv->m13 = m[7];

    uniformMatrix4fv->m20 = m[8];
    uniformMatrix4fv->m21 = m[9];
    uniformMatrix4fv->m22 = m[10];
    uniformMatrix4fv->m23 = m[11];
    
    uniformMatrix4fv->m30 = m[12];
    uniformMatrix4fv->m31 = m[13];
    uniformMatrix4fv->m32 = m[14];
    uniformMatrix4fv->m33 = m[15];
    
    glUniformMatrix4fv(location, count, transpose, m);
}

inline void jmpGLUniformMatrix3fv(const GLuint &programId, const GLint &location, const GLsizei &count, const bool &transpose, const GLfloat* m)
{
    glUniformMatrix3fv(location, count, transpose, m);
    return;
    
    static std::map<std::pair<GLuint, GLint>, UniformMatrix3fv> uniformMatrix3fvs;
    
    UniformMatrix3fv *uniformMatrix3fv = &uniformMatrix3fvs[std::make_pair(programId, location)];
    if(uniformMatrix3fv->location == location
       && uniformMatrix3fv->count == count
       && uniformMatrix3fv->m00 == m[0]
       && uniformMatrix3fv->m01 == m[1]
       && uniformMatrix3fv->m02 == m[2]
       
       && uniformMatrix3fv->m10 == m[3]
       && uniformMatrix3fv->m11 == m[4]
       && uniformMatrix3fv->m12 == m[5]
       
       && uniformMatrix3fv->m20 == m[6]
       && uniformMatrix3fv->m21 == m[7]
       && uniformMatrix3fv->m22 == m[8])
    {
        return;
    }
    
    uniformMatrix3fv->location = location;
    uniformMatrix3fv->count = count;
    uniformMatrix3fv->m00 = m[0];
    uniformMatrix3fv->m01 = m[1];
    uniformMatrix3fv->m02 = m[2];
    
    uniformMatrix3fv->m10 = m[3];
    uniformMatrix3fv->m11 = m[4];
    uniformMatrix3fv->m12 = m[5];
    
    uniformMatrix3fv->m20 = m[6];
    uniformMatrix3fv->m21 = m[7];
    uniformMatrix3fv->m22 = m[8];
    
    glUniformMatrix3fv(location, count, transpose, m);
}

inline void jmpGLUniform3fv(const GLuint &programId, const GLint &location, const GLsizei &count, const GLfloat* v)
{
    glUniform3fv(location, count, v);
    return;
    
    static std::map<std::pair<GLuint, GLint>, Uniform3fv> uniform3fvs;
    
    Uniform3fv *uniform3fv = &uniform3fvs[std::make_pair(programId, location)];
    if(uniform3fv->location == location
        && uniform3fv->count == count
        && uniform3fv->x == v[0]
        && uniform3fv->y == v[1]
        &&uniform3fv->z == v[2])
    {
        return;
    }
    
    uniform3fv->location = location;
    uniform3fv->count = count;
    uniform3fv->x = v[0];
    uniform3fv->y = v[1];
    uniform3fv->z = v[2];
    
    glUniform3fv(location, count, v);
}

inline void jmpGLUniform4fv(const GLuint &programId, const GLint &location, const GLsizei &count, const GLfloat* v)
{
    glUniform4fv(location, count, v);
    return;
    
    static std::map<std::pair<GLuint, GLint>, Uniform4fv> uniform4fvs;
    
    Uniform4fv *uniform4fv = &uniform4fvs[std::make_pair(programId, location)];
    if(uniform4fv->location == location
       && uniform4fv->count == count
       && uniform4fv->x == v[0]
       && uniform4fv->y == v[1]
       && uniform4fv->z == v[2]
       && uniform4fv->w == v[3])
    {
        return;
    }
    
    uniform4fv->location = location;
    uniform4fv->count = count;
    uniform4fv->x = v[0];
    uniform4fv->y = v[1];
    uniform4fv->z = v[2];
    uniform4fv->w = v[3];
    
    glUniform4fv(location, count, v);
}


inline void jmpGLUniform1i(const GLuint &programId, const GLint &location, const GLint &x)
{
    glUniform1i(location, x);
    return;
    
    static std::map<std::pair<GLuint, GLint>, Uniform1i> uniform1is;
    
    Uniform1i *uniform1i = &uniform1is[std::make_pair(programId, location)];
    if(uniform1i->location == location
       && uniform1i->x == x)
    {
        return;
    }
    
    uniform1i->location = location;
    uniform1i->x = x;
    
    glUniform1i(location, x);
}

inline void jmpGLUniform1f(const GLuint &programId, const GLint &location, const GLfloat &x)
{
    glUniform1f(location, x);
    return;
    
    static std::map<std::pair<GLuint, GLint>, Uniform1f> uniform1fs;
    
    Uniform1f *uniform1f = &uniform1fs[std::make_pair(programId, location)];
    if(uniform1f->location == location
       && uniform1f->x == x)
    {
        return;
    }
    
    uniform1f->location = location;
    uniform1f->x = x;
    
    glUniform1f(location, x);
}

#endif /* _GL_H */
