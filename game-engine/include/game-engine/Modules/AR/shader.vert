
#version 300 es

// In variables
in vec3 position;
in vec2 texCoord;

// Out variables
out mediump vec2 TexCoord;

void main()
{
   TexCoord = texCoord;
   gl_Position = vec4(position, 1.0);
}

