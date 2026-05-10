#include <glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "constants.h"
#include "scene.h"
#include "shader.h"
#include "textures.h"

Box boxes[BOX_COUNT];

// =========================
// PÚBLICAS
// =========================
// Configura la geometría OpenGL de un cubo
// - El buffer contiene posición y color por vértice
// - En esta configuración solo se habilita el atributo de posición
void configObject(BodyPart &object)
{
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
    
    // Generar VAO y VBO
    glGenVertexArrays(1, &object.VAO);
    glGenBuffers(1, &object.VBO);

    glBindVertexArray(object.VAO); // El VAO comienza a "grabar"

    // Enviar datos al VBO
    glBindBuffer(GL_ARRAY_BUFFER, object.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Atributo 0: posición (vec3)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Atributo 1: normal (vec3)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Atributo 2: coordenada de textura (vec2)
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void initRoom(Room &room, GLuint shaderProgram)
{
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

// INICIALIZAR LAS CAJAS
void initBoxes(Box b[])
{
    // Estructura temporal, solo para la inicialización
    struct BoxDef
    {
        glm::vec3 pos;
        glm::vec3 scale;
        float yRot;
    };

    BoxDef defs[BOX_COUNT] = {
        { {  3.0f, 1.0f, -20.0f }, { 2.0f, 2.0f, 2.0f },  15.0f },
        { {  3.0f, 3.0f, -20.0f }, { 2.0f, 2.0f, 2.0f },  -8.0f }, // encima
        { { -3.0f, 1.0f,  -5.0f }, { 2.0f, 2.0f, 2.0f },  30.0f },
        { {  3.0f, 1.5f,  10.0f }, { 2.5f, 3.0f, 2.5f },   0.0f },
        { {  0.0f, 1.0f,  20.0f }, { 2.0f, 2.0f, 2.0f },  45.0f },
        { { -3.0f, 1.0f,  30.0f }, { 2.0f, 2.0f, 2.0f }, -20.0f },
    };

    // Iterar sobre las cajas, cargar la textura e inicializar valores
    for (int i = 0; i < BOX_COUNT; i++)
    {
        configObject(b[i].body);
        b[i].body.textureID = loadTexture("textures/box.jpg");
        b[i].body.vertexCount = VERTEX_COUNT;
        b[i].position = defs[i].pos;
        b[i].scale = defs[i].scale;
        b[i].yRot = defs[i].yRot;
    }
}

// DIBUJAR LAS CAJAS
void drawBoxes(Box boxes[], Shader shader)
{
    // Realizar transformaciones
    for (int i = 0; i < BOX_COUNT; i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, boxes[i].position);
        model = glm::rotate(model, glm::radians(boxes[i].yRot), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, boxes[i].scale);
    
        // Enviar al shader
        shaderSetMat4(shader, "model", model);
        shaderSetVec2(shader, "uvScale", glm::vec2(1.0f, 1.0f));

        // Activar y enlazar textura
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, boxes[i].body.textureID);
        glBindVertexArray(boxes[i].body.VAO);
        glDrawArrays(GL_TRIANGLES, 0, boxes[i].body.vertexCount);
        glBindVertexArray(0);
    }
}

// DIBUJAR EL PASILLO
void drawRoom(Room &room, Shader shader)
{
    // Un struct almacena cada parte del pasillo
    struct Piece
    {
        BodyPart &part;
        glm::vec3 pos;
        glm::vec3 scale;
        glm::vec2 uvScale;
    };

    Piece pieces[] = {
        { room.floor,     { 0, -WALL_THICKNESS / 2, 0              }, { HALL_WIDTH, WALL_THICKNESS, HALL_LENGTH  }, { HALL_WIDTH / TILE_SIZE, HALL_LENGTH / TILE_SIZE } },
        { room.ceiling,   { 0, HALL_HEIGHT + WALL_THICKNESS / 2, 0 }, { HALL_WIDTH, WALL_THICKNESS, HALL_LENGTH  }, { HALL_WIDTH / TILE_SIZE, HALL_LENGTH / TILE_SIZE } },
        { room.wallFront, { 0, HALL_HEIGHT / 2, -HALL_LENGTH / 2   }, { HALL_WIDTH, HALL_HEIGHT, WALL_THICKNESS  }, { HALL_WIDTH / TILE_SIZE, HALL_HEIGHT / TILE_SIZE } },
        { room.wallBack,  { 0, HALL_HEIGHT / 2, HALL_LENGTH / 2    }, { HALL_WIDTH, HALL_HEIGHT, WALL_THICKNESS  }, { HALL_WIDTH / TILE_SIZE, HALL_HEIGHT / TILE_SIZE } },
        { room.wallRight, { HALL_WIDTH / 2, HALL_HEIGHT / 2, 0     }, { WALL_THICKNESS, HALL_HEIGHT, HALL_LENGTH }, { HALL_WIDTH / TILE_SIZE, HALL_HEIGHT / TILE_SIZE } },
        { room.wallLeft,  { -HALL_WIDTH / 2, HALL_HEIGHT / 2, 0    }, { WALL_THICKNESS, HALL_HEIGHT, HALL_LENGTH }, { HALL_WIDTH / TILE_SIZE, HALL_HEIGHT / TILE_SIZE } },
    };

    // Iterar sobre cada parte, calcular su modelo y dibujarlo
    for (auto &p : pieces)
    {
        // Realizar transformaciones
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, p.pos);
        model = glm::scale(model, p.scale);

        // Enviar al shader
        shaderSetMat4(shader, "model", model);
        shaderSetVec2(shader, "uvScale", p.uvScale);

        // Activar y enlazar texturas
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, p.part.textureID);
        glBindVertexArray(p.part.VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
    }
}