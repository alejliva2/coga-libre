#include <glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "constants.h"
#include "esfera.h"
#include "scene.h"
#include "shader.h"
#include "textures.h"

// =========================
// VARIABLES GLOBALES
// =========================
Room room;


// =========================
// PÚBLICAS
// =========================

// Configura la geometría OpenGL de la articulación esférica
// El formato de cada vértice en vertices_esfera es:
// - normal (3 floats)
// - coordenada de textura (2 floats)
// - posición (3 floats)

void configSphere(BodyPart &object) {
    glGenVertexArrays(1, &object.VAO);
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
    object.vertexCount = sizeof(vertices_esfera) / (8 * sizeof(float));

}

// Configura la geometría OpenGL de un cubo
// - El buffer contiene posición y color por vértice
// - En esta configuración solo se habilita el atributo de posición
void configObject(BodyPart& object) {
    float vertices[] = {
        // Cubo formado por 6 caras, cada una compuesta por 2 triángulos
        // Total: 36 vértices.
        // pos(3)          normal(3)           uv(2)
        // Cara frontal (z = 0.5)
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,

        // Cara trasera (z = -0.5)
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  1.0f, 0.0f,

        // Cara derecha (x = 0.5)
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,

        // Cara izquierda (x = -0.5)
        -0.5f, -0.5f,  0.5f, -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f, -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f, -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,

        // Cara superior (y = 0.5)
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,

        // Cara inferior (y = -0.5)
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f,  0.0f, 0.0f,
    };

    
    glGenVertexArrays(1, &object.VAO);
    glGenBuffers(1, &object.VBO);
    
    glBindVertexArray(object.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, object.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // Atributo 0: posición (vec3)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // Atributo 1: normal (vec3)    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    // Atributo 2: coordenada textura (vec2)
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}


void initRoom(Room &room, GLuint shaderProgram) {
    // Configurar cada parte de la habitación
    configObject(room.floor);
    configObject(room.ceiling);
    configObject(room.wallFront);
    configObject(room.wallBack);
    configObject(room.wallLeft);
    configObject(room.wallRight);

    // Cargar texturas
    room.floor.textureID = loadTexture("textures/floor.jpg");
    room.ceiling.textureID = loadTexture("textures/ceiling.jpg");
    room.wallFront.textureID = loadTexture("textures/wall.jpg");
    room.wallBack.textureID = loadTexture("textures/wall.jpg");
    room.wallLeft.textureID = loadTexture("textures/wall.jpg");
    room.wallRight.textureID = loadTexture("textures/wall.jpg");

    // Obtener la ubicación del uniform "model" en el shader
    room.modelLoc = glGetUniformLocation(shaderProgram, "model");
}

void drawRoom(Room &room, Shader shader)
{
    // Hacemos un struct para almacenar la información de cada parte de la habitación 
    struct Piece { BodyPart &part; glm::vec3 pos; glm::vec3 scale; };
    Piece pieces[] = {
        { room.floor,     {    0,   0,    0 }, { ROOM_WIDTH,  WALL_THICKNESS,  ROOM_DEPTH } },
        { room.ceiling,   {    0,   ROOM_HEIGHT,    0 }, { ROOM_WIDTH,  WALL_THICKNESS,  ROOM_DEPTH } },
        { room.wallFront, {    0, ROOM_HEIGHT/2, -ROOM_DEPTH/2 }, { ROOM_WIDTH,  ROOM_HEIGHT,  WALL_THICKNESS } },
        { room.wallBack,  {    0, ROOM_HEIGHT/2,  ROOM_DEPTH/2 }, { ROOM_WIDTH,  ROOM_HEIGHT,  WALL_THICKNESS } },
        { room.wallRight, {  ROOM_WIDTH/2, ROOM_HEIGHT/2,    0 }, { WALL_THICKNESS,  ROOM_HEIGHT,  ROOM_DEPTH } },
        { room.wallLeft,  { -ROOM_WIDTH/2, ROOM_HEIGHT/2,    0 }, { WALL_THICKNESS,  ROOM_HEIGHT,  ROOM_DEPTH } },
    };

    // Iteramos sobre cada parte, calculamos su modelo y la dibujamos
    for (auto &p : pieces)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, p.pos);
        model = glm::scale(model, p.scale);
        shaderSetMat4(shader, "model", model);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, p.part.textureID);

        glBindVertexArray(p.part.VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
    }
}
