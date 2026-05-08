#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

// =========================
// LOG
// =========================
const unsigned int LOG_SIZE = 512;

// =========================
// VENTANA
// =========================
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const glm::vec4 CLEAR_COLOR = glm::vec4(0.02f, 0.02f, 0.06f, 1.0f);

// =========================
// CÁMARA
// =========================
const float HEIGHT_EYE = 1.8f; // Altura del ojo para la cámara (altura promedio de una persona)

const float CAM_INITIAL_YAW   = -90.0f;
const float CAM_INITIAL_PITCH =   0.0f;
const float CAM_FOV           =  60.0f;
const float CAM_SPEED         =   1.0f;
const float CAM_SENSITIVITY   =   0.01f;
const float CAM_FAR_PLANE     = 100.0f;
const float CAM_NEAR_PLANE    =   0.1f;
const glm::vec3 CAM_WORLD_UP  = glm::vec3(0.0f, 1.0f, 0.0f);

const int CAM_MODE_FIRST_PERSON = 1;
const int CAM_MODE_THIRD_PERSON = 3;

// ========================
// ESCENARIO
// ========================
const float ROOM_WIDTH  = 30.0f;
const float ROOM_HEIGHT = 6.0f;
const float ROOM_DEPTH  = 30.0f;
const float WALL_THICKNESS = 0.1f;

// =========================
// LUZ
// =========================
const float FLASHLIGHT_AMBIENT = 0.35f;
const float FLASHLIGHT_DIFFUSE = 0.2f;
const float FLASHLIGHT_SPECULAR = 0.01f;
const float FLASHLIGHT_SPECULAR_STRENGTH = 0.5f;

const float FLASHLIGHT_INNER_ANGLE = 12.00f; 
const float FLASHLIGHT_OUTER_ANGLE = 40.0f;

// =========================
// PERSONAJE
// =========================
const glm::vec3 HEAD_POSITION = glm::vec3(0.0f, 1.2f, 0.0f);
const glm::vec3 HEAD_SCALE = glm::vec3(0.75f, 0.75f, 0.75f);

const glm::vec3 TORSO_POSITION = glm::vec3(0.0f, 0.3f, 0.0f);
const glm::vec3 TORSO_SCALE = glm::vec3(1.2f, 1.2f, 0.4f);

const glm::vec3 LEFT_ARM_POSITION = glm::vec3(-0.75f, 0.3f, 0.0f);
const glm::vec3 RIGHT_ARM_POSITION = glm::vec3(0.75f, 0.3f, 0.0f);
const glm::vec3 ARM_SCALE = glm::vec3(0.3f, 1.2f, 0.4f);

const glm::vec3 LEFT_LEG_POSITION = glm::vec3(-0.4f, -1.0f, 0.0f);
const glm::vec3 RIGHT_LEG_POSITION = glm::vec3(0.4f, -1.0f, 0.0f);
const glm::vec3 LEG_SCALE = glm::vec3(0.4f, 1.5f, 0.4f);

const glm::vec3 FLASHLIGHT_POSITION_FIRST_PERSON = glm::vec3(0.35f, 1.0f, 0.0f); // Posición de la linterna en la mano del personaje
const glm::vec3 FLASHLIGHT_POSITION_THIRD_PERSON = glm::vec3(0.7f, 0.0f, -0.3f); // Posición de la linterna en la mano del personaje
const glm::vec3 FLASHLIGHT_SCALE = glm::vec3(0.2f, 0.2f, 0.6f);

const glm::vec3 FP_RIGHT_ARM_OFFSET = glm::vec3(0.5f, -0.75f, 0.5f); // Offset de la mano del personaje en primera persona
const glm::vec3 FP_FLASHLIGHT_OFFSET = glm::vec3(0.35f, 0.0f, 1.0f); // Offset de la linterna en primera persona

const unsigned int VERTEX_COUNT = 36; // Número de vértices para un cubo (6 caras * 2 triángulos por cara * 3 vértices por triángulo)


#endif // CONSTANTS_H