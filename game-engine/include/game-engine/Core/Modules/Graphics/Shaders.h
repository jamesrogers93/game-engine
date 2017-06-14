#include <string>

static const std::string basicVertex =
" #version 300 es\n"
"// In variables\n"
"in vec3 position;\n"
"in vec3 normal;\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(position, 1.0);\n"
"}\n\0";

static const std::string basicFragment =
"#version 300 es\n"
"// In variables\n"
"in mediump vec3 Normal;\n"
"// Out variables\n"
"out mediump vec4 colour;\n"
"// Uniform Variables\n"
"uniform mediump vec4 diffuseSolid;\n"
"void main()\n"
"{\n"
"    colour = vec4(1.0, 0.0, 0.0, 1.0);\n"
"    //colour = diffuseSolid;\n"
"}\n\0";
