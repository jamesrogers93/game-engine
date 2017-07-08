#ifndef _OPENGL_H
#define _OPENGL_H

// OpenGL
#ifdef __ANDROID__
    #include <GLES3/gl3.h>
    #include <EGL/egl.h>

#elif __IOS__
    #define GL_GLEXT_PROTOTYPES
    #include <OpenGLES/ES3/gl.h>
    #include <OpenGLES/ES3/glext.h>

#elif __MACOS__
    #include <OpenGL/gl3.h>

#else
    #ifdef _WIN32
        #include <windows.h>
    #endif
    #include <GL/glew.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
    //#include <GL/glut.h>
#endif

#endif