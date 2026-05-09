#ifndef SCENE_H
#define SCENE_H

#include "character.h"
#include "shader.h"

// =========================
// ESCENA
// =========================
struct Room
{
    BodyPart floor;
    BodyPart ceiling;
    BodyPart wallFront;
    BodyPart wallBack;
    BodyPart wallLeft;
    BodyPart wallRight;

    GLuint modelLoc; // Ubicación del uniform "model" en el shader
};

struct Box
{
    BodyPart body;
    glm::vec3 position;
    glm::vec3 scale;
    float yRot; // Rotación en Y para que no estén todas alineadas
};

void configSphere(BodyPart &object);
void configObject(BodyPart &object);
void initRoom(Room &room, GLuint shaderProgram);
void initBoxes(Box boxes[]);
void drawRoom(Room &room, Shader shader);
void drawBoxes(Box boxes[], Shader shader);

#endif // SCENE_H