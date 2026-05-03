#ifndef SCENE_H
#define SCENE_H

#include "shader.h"
#include "character.h"


typedef struct
{
    BodyPart floor;
    BodyPart ceiling;
    BodyPart wallFront;
    BodyPart wallBack;
    BodyPart wallLeft;
    BodyPart wallRight;

    GLuint modelLoc; // ubicación del uniform "model" en el shader
} Room;

extern Room room;

// =========================
// FUNCIONES
// =========================
void configSphere(BodyPart &object);
void configObject(BodyPart &object);
void initRoom(Room &room, GLuint shaderProgram);
void drawRoom(Room &room, Shader shader);

#endif // SCENE_H