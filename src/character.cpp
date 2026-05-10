#include <glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "camera.h"
#include "character.h"
#include "constants.h"
#include "scene.h"
#include "shader.h"
#include "textures.h"

// =========================
// HELPERS
// =========================
namespace
{
    void _drawPart(const BodyPart &part,
                   Shader shader,
                   const glm::vec3 &characterPosition = glm::vec3(0.0f),
                   float characterYaw = 0.0f,
                   float xRotDeg = 0.0f)
    {
        // Construir la matriz de cada parte
        // 1. Escalar el cubo
        // 2. Rotar la parte sobre su propio centro
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, characterPosition);                                       // 5
        model = glm::rotate(model, glm::radians(characterYaw), glm::vec3(0.0f, 1.0f, 0.0f));    // 4
        model = glm::translate(model, part.position);                                           // 3
        model = glm::rotate(model, glm::radians(part.transAngle), glm::vec3(0.0f, 1.0f, 0.0f)); // 2
        if (xRotDeg != 0.0f)
        {
            // Subir al pivote (cadera = mitad superior de la pierna)
            glm::vec3 pivot = glm::vec3(0.0f, part.scale.y * 0.5f, 0.0f);
            model = glm::translate(model, pivot);
            model = glm::rotate(model, glm::radians(xRotDeg), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::translate(model, -pivot);
        }
        model = glm::scale(model, part.scale); // 1

        // Enviar matriz al shader
        shaderSetMat4(shader, "model", model);
        shaderSetInt(shader, "diffuseTex", 0);
        shaderSetVec2(shader, "uvScale", glm::vec2(1.0f, 1.0f));

        // Establecer texturas
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, part.textureID);
        glBindVertexArray(part.VAO);
        glDrawArrays(GL_TRIANGLES, 0, part.vertexCount);
        glBindVertexArray(0);
    }

    // Para el bloque de primera persona
    void _drawViewModel(const BodyPart &part, Shader shader, const Camera &camera)
    {
        // Construir una matriz de rotación con los ejes de la cámara
        glm::mat4 orientation = glm::mat4(1.0f);

        orientation[0] = glm::vec4(camera.right, 0.0f);  // Eje X = right
        orientation[1] = glm::vec4(camera.up, 0.0f);     // Eje Y = up
        orientation[2] = glm::vec4(-camera.front, 0.0f); // Eje Z = -front (OpenGL mira hacia -Z)
        orientation[3] = glm::vec4(part.position, 1.0f);

        glm::mat4 model = orientation * glm::scale(glm::mat4(1.0f), part.scale);

        // Enviar matriz al shader
        shaderSetMat4(shader, "model", model);
        shaderSetVec2(shader, "uvScale", glm::vec2(1.0f, 1.0f));

        // Establecer texturas
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
// INICIALIZAR PERSONAJE
void initCharacter(Character &character)
{
    character.position = glm::vec3(0.0f, 0.0f, 0.0f);

    // Configurar cada parte del personaje
    configObject(character.head);
    configObject(character.torso);
    configObject(character.leftArm);
    configObject(character.rightArm);
    configObject(character.leftLeg);
    configObject(character.rightLeg);
    configObject(character.flashlight);

    character.head.position = HEAD_POSITION;
    character.head.transAngle = 0.0f;
    character.head.scale = HEAD_SCALE;
    character.head.vertexCount = VERTEX_COUNT;

    character.torso.position = TORSO_POSITION;
    character.torso.transAngle = 0.0f;
    character.torso.scale = TORSO_SCALE;
    character.torso.vertexCount = VERTEX_COUNT;

    character.leftArm.position = LEFT_ARM_POSITION;
    character.leftArm.transAngle = 0.0f;
    character.leftArm.scale = ARM_SCALE;
    character.leftArm.vertexCount = VERTEX_COUNT;

    character.rightArm.position = RIGHT_ARM_POSITION;
    character.rightArm.transAngle = 0.0f;
    character.rightArm.scale = ARM_SCALE;
    character.rightArm.vertexCount = VERTEX_COUNT;

    character.leftLeg.position = LEFT_LEG_POSITION;
    character.leftLeg.transAngle = 0.0f;
    character.leftLeg.scale = LEG_SCALE;
    character.leftLeg.vertexCount = VERTEX_COUNT;

    character.rightLeg.position = RIGHT_LEG_POSITION;
    character.rightLeg.transAngle = 0.0f;
    character.rightLeg.scale = LEG_SCALE;
    character.rightLeg.vertexCount = VERTEX_COUNT;

    character.flashlight.position = TP_FLASHLIGHT_POSITION;
    character.flashlight.transAngle = 0.0f;
    character.flashlight.scale = FLASHLIGHT_SCALE;
    character.flashlight.vertexCount = VERTEX_COUNT;

    // Configurar las texturas de cada parte del personaje
    character.head.textureID = loadTexture("textures/head.jpg");
    character.torso.textureID = loadTexture("textures/arm.jpg"); // ponemos la misma textura en la "camiseta"
    character.leftArm.textureID = loadTexture("textures/arm.jpg");
    character.rightArm.textureID = loadTexture("textures/arm.jpg");
    character.leftLeg.textureID = loadTexture("textures/leg.jpeg");
    character.rightLeg.textureID = loadTexture("textures/leg.jpeg");
    character.flashlight.textureID = loadTexture("textures/wall.jpg");
}

void drawCharacter(Character &character, Shader shader, const Camera &camera)
{
    glm::vec3 position = character.position;
    // Orientación del personaje (mirando hacia la cámara)
    float orientation = -camera.yaw - 90.0f;

    if (camera.mode == CAM_MODE_THIRD_PERSON)
    {
        // Actualizar para que el brazo derecho se queda en la posición de la primera persona
        character.rightArm.position = RIGHT_ARM_POSITION;

        // Posición de la linterna en la mano del personaje en tercera persona
        // Hombro derecho = extremo superior del brazo
        glm::vec3 shoulder = RIGHT_ARM_POSITION + glm::vec3(0.0f, ARM_SCALE.y * 0.5f, 0.0f);

        // Posición que tendría la linterna si el brazo no estuviera rotado
        glm::vec3 flashlightRest = RIGHT_ARM_POSITION + TP_FLASHLIGHT_POSITION_OFFSET;

        // Rotarla alrededor del hombro el mismo ángulo que el brazo
        glm::vec3 offsetFromShoulder = flashlightRest - shoulder;
        glm::mat4 rot = glm::rotate(glm::mat4(1.0f),
                                    glm::radians(RIGHT_ARM_RAISED_ANGLE),
                                    glm::vec3(1.0f, 0.0f, 0.0f));
        glm::vec3 rotatedOffset = glm::vec3(rot * glm::vec4(offsetFromShoulder, 1.0f));
        character.flashlight.position = shoulder + rotatedOffset;

        _drawPart(character.head, shader, character.position, orientation);
        _drawPart(character.torso, shader, character.position, orientation);
        _drawPart(character.leftArm, shader, character.position, orientation);
        _drawPart(character.rightArm, shader, character.position, orientation, RIGHT_ARM_RAISED_ANGLE);
        _drawPart(character.leftLeg, shader, character.position, orientation, character.leftLegAngle);
        _drawPart(character.rightLeg, shader, character.position, orientation, character.rightLegAngle);
        _drawPart(character.flashlight, shader, character.position, orientation);
    }

    if (camera.mode == CAM_MODE_FIRST_PERSON)
    {
        character.rightArm.position = camera.position +
                                      camera.right * FP_RIGHT_ARM_OFFSET.x +
                                      camera.up * FP_RIGHT_ARM_OFFSET.y +
                                      camera.front * FP_RIGHT_ARM_OFFSET.z;

        character.flashlight.position = character.rightArm.position +
                                        camera.front * FP_FLASHLIGHT_OFFSET.z +
                                        camera.up * FP_FLASHLIGHT_OFFSET.y +
                                        camera.right * FP_FLASHLIGHT_OFFSET.x;

        _drawViewModel(character.rightArm, shader, camera);
        _drawViewModel(character.flashlight, shader, camera);
    }
}

void updateCharacter(Character &character, float deltaTime)
{
    // Si se está moviendo
    if (character.isMoving)
    {
        // Actualizar los ángulos de las piernas
        // Uno debe ser positivo y otro negativo
        character.walkTimer += deltaTime * LEG_SWING_SPEED;
        character.leftLegAngle = LEG_SWING_AMPLITUDE * std::sin(character.walkTimer);
        character.rightLegAngle = -LEG_SWING_AMPLITUDE * std::sin(character.walkTimer);
    }
    else
    {
        // Volver suevamente a 0 cuando para
        character.leftLegAngle *= DECELERATION_FACTOR;
        character.rightLegAngle *= DECELERATION_FACTOR;
    }
}