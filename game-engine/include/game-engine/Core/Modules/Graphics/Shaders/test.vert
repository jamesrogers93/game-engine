#version 300 es

// In variables
in vec3 position;
in vec3 normal;

// Out variables
out mediump vec3 Normal;

void main()
{
    Normal = normal;
    gl_Position = vec4(position, 1.0);
}