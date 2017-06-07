#pragma once

// OpenGL
#ifdef __ANDROID__
#include <GLES3/gl3.h>
#include <EGL/egl.h>

#elif __iOS__
#define GL_GLEXT_PROTOTYPES
#include <OpenGLES/ES3/gl.h>

#elif __macOS__
#include <OpenGL/gl3.h>

#endif
