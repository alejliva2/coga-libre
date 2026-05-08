#include <glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "camera.h"
#include "character.h"
#include "constants.h"
#include "scene.h"
#include "shader.h"
#include "textures.h"

Character character;


// =========================
// HELPERS
// =========================
namespace 
{
    void _drawPart(const BodyPart &part, Shader shader, const glm::vec3 &offset = glm::vec3(0.0f))
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, part.position + offset);
        model = glm::rotate(model, glm::radians(part.transAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, part.scale);

        shaderSetMat4(shader, "model", model);
        shaderSetInt(shader, "diffuseTex", 0);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, part.textureID);
        glBindVertexArray(part.VAO);
        glDrawArrays(GL_TRIANGLES, 0, part.vertexCount);
        glBindVertexArray(0);
    }
}


// =========================
// PÚBLICAS
// =========================

void initCharacter(Character &ch)
{
    ch.position = glm::vec3(0.0f, 0.0f, 0.0f);

    // Configuramos cada parte del personaje
    configObject(ch.head);
    configObject(ch.torso);
    configObject(ch.leftArm);
    configObject(ch.rightArm);
    configObject(ch.leftLeg);
    configObject(ch.rightLeg);
    configObject(ch.flashlight);

    ch.head.position = HEAD_POSITION;
    ch.head.scale = HEAD_SCALE;
    ch.head.vertexCount = VERTEX_COUNT;

    ch.torso.position = TORSO_POSITION;
    ch.torso.scale = TORSO_SCALE;
    ch.torso.vertexCount = VERTEX_COUNT;

    ch.leftArm.position = LEFT_ARM_POSITION;
    ch.leftArm.scale = ARM_SCALE;
    ch.leftArm.vertexCount = VERTEX_COUNT;

    ch.rightArm.position = RIGHT_ARM_POSITION;
    ch.rightArm.scale = ARM_SCALE;
    ch.rightArm.vertexCount = VERTEX_COUNT;

    ch.leftLeg.position = LEFT_LEG_POSITION;
    ch.leftLeg.scale = LEG_SCALE;
    ch.leftLeg.vertexCount = VERTEX_COUNT;

    ch.rightLeg.position = RIGHT_LEG_POSITION;
    ch.rightLeg.scale = LEG_SCALE;
    ch.rightLeg.vertexCount = VERTEX_COUNT;

    ch.flashlight.position = FLASHLIGHT_POSITION_FIRST_PERSON;
    ch.flashlight.scale = FLASHLIGHT_SCALE;
    ch.flashlight.vertexCount = VERTEX_COUNT;

    // Configuamos las texturas de cada parte del personaje
    ch.head.textureID = loadTexture("textures/head.jpg");
    ch.torso.textureID = loadTexture("textures/arm.jpg"); // ponemos la misma textura en la "camiseta"
    ch.leftArm.textureID = loadTexture("textures/arm.jpg");
    ch.rightArm.textureID = loadTexture("textures/arm.jpg");
    ch.leftLeg.textureID = loadTexture("textures/leg.jpeg");
    ch.rightLeg.textureID = loadTexture("textures/leg.jpeg");
    ch.flashlight.textureID = loadTexture("textures/blackMetal.jpg");
}


void drawCharacter(Character &ch, Shader shader, const Camera &cam)
{
    glm::vec3 position = ch.position;
    float orientation = -cam.yaw + 90.0f; // Orientación del personaje (mirando hacia la cámara)


    if (cam.mode == CAM_MODE_THIRD_PERSON)
    {
        ch.rightArm.position = RIGHT_ARM_POSITION; // actualizamos porque sino el brazo derecho se queda en la posición de la primera persona
        ch.flashlight.position = FLASHLIGHT_POSITION_THIRD_PERSON; // Posición de la linterna en la mano del personaje en tercera persona

        _drawPart(ch.head, shader, ch.position);
        _drawPart(ch.torso, shader, ch.position);
        _drawPart(ch.leftArm, shader, ch.position);
        _drawPart(ch.rightArm, shader, ch.position);
        _drawPart(ch.leftLeg, shader, ch.position);
        _drawPart(ch.rightLeg, shader, ch.position);
        _drawPart(ch.flashlight, shader, ch.position);
    }

    if (cam.mode == CAM_MODE_FIRST_PERSON)
    {
        ch.rightArm.position = cam.position + cam.right * FP_RIGHT_ARM_OFFSET.x + cam.up * FP_RIGHT_ARM_OFFSET.y + cam.front * FP_RIGHT_ARM_OFFSET.z;
        ch.flashlight.position = ch.rightArm.position + cam.front * FP_FLASHLIGHT_OFFSET.z + cam.up * FP_FLASHLIGHT_OFFSET.y + cam.right * FP_FLASHLIGHT_OFFSET.x;

        _drawPart(ch.rightArm, shader);
        _drawPart(ch.flashlight, shader);
    }   
}

