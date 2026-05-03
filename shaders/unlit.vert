#version 330 core

layout (location = 0) in vec3 position; // Posición
layout (location = 2) in vec2 texcoord; // Coords. textura

uniform mat4 model;      // Modelo
uniform mat4 view;       // Vista
uniform mat4 projection; // Proyección

out vec2 texCoord; // Coords. textura

void main()
{
    // Coordenadas de textura
    texCoord = texcoord;
    // Posición final del vértice
    gl_Position = projection * view * model * vec4(position, 1.0);
}