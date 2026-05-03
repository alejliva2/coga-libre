#version 330 core

layout (location = 0) in vec3 position; // Posición
layout (location = 1) in vec3 normal;   // Normal
layout (location = 2) in vec2 texcoord; // Coords. textura

uniform mat4 model;      // Modelo
uniform mat4 view;       // Vista
uniform mat4 projection; // Proyección

out vec3 wPos;     // Posición espacio mundo
out vec3 wNormal;  // Normal espacio mundo 
out vec2 texCoord; // Coords. textura

void main()
{
    // Posición en espacio mundo
    wPos = vec3(model * vec4(position, 1.0));
    // Normal en espacio mundo
    wNormal = mat3(transpose(inverse(model))) * normal;
    // Coordenadas de textura
    texCoord = texcoord;
    // Posición final del vértice
    gl_Position = projection * view * vec4(wPos, 1.0);
}