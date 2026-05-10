#ifndef CHARACTER_H
#define CHARACTER_H

#include <glad.h>
#include <glm/glm.hpp>

#include "shader.h"
#include "camera.h"

// =========================
// CHARACTER
// =========================
typedef struct
{
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 color;
    float transAngle;
    float speed;
    unsigned int VAO;
    unsigned int VBO;
    unsigned int vertexCount;
    GLuint textureID;
} BodyPart;


typedef struct
{
    BodyPart head;
    BodyPart torso;
    BodyPart leftArm;
    BodyPart rightArm;
    BodyPart leftLeg;
    BodyPart rightLeg;

    BodyPart flashlight;

    glm::vec3 position;

    // Movimiento
    bool isMoving;
    float walkTimer;
    float leftLegAngle;
    float rightLegAngle;
} Character;

void initCharacter(Character &character);
void drawCharacter(Character &character, Shader shader, const Camera &camera);
void updateCharacter(Character &character, float deltaTime);

#endif // CHARACTER_H