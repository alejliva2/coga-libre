#include <glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stb_image.h>

#include "scene.h"

// Configura la geometría OpenGL de la articulación esférica
// El formato de cada vértice en vertices_esfera es:
// - normal (3 floats)
// - coordenada de textura (2 floats)
// - posición (3 floats)
/*
void configSphere(Something &something) {
    glGenVertexArrays(1, &something.VAO);
    glGenBuffers(1, &object.VBO);

    glBindVertexArray(object.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, object.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_esfera), vertices_esfera, GL_STATIC_DRAW);

    // Atributo 0: posición (vec3)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(0);

    // Atributo 1: normal (vec3)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    // Atributo 2: coordenada de textura (vec2)
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}
*/