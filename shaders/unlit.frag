#version 330 core

in vec2 texCoord; // Coords. textura

uniform sampler2D diffuseTex; // Textura difusa

out vec4 fragColor; // Color final del píxel

void main()
{
    fragColor = texture(diffuseTex, texCoord);
}