#version 300 es

// In variables
in mediump vec2 TexCoord;
in mediump vec3 Normal;
in mediump vec3 FragPos;

// Out variables
out mediump vec4 colour;

// Uniform Variables
uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;
uniform mediump vec4 diffuseSolid;
uniform mediump vec4 specularSolid;
uniform mediump float shininess;

void main()
{
    colour = diffuseSolid;
}