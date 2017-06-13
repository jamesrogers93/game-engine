#version 300 es

// In variables
in vec3 position;
in vec3 normal;
in vec2 texCoord;

// Out variables
out mediump vec2 TexCoord;
out mediump vec3 Normal;

void main()
{
    TexCoord = texCoord;
    Normal = normal;
    glPosition = vec4(position);
}