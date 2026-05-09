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
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;
const glm::vec4 CLEAR_COLOR = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

// =========================
// CÁMARA
// =========================
const float HEIGHT_EYE = 1.7f; // Altura del ojo para la cámara (altura promedio de una persona)

const float CAM_INITIAL_YAW   = 90.0f;
const float CAM_INITIAL_PITCH =   0.0f;
const float CAM_FOV           =  75.0f;
const float CAM_SPEED         =   5.0f;
const float CAM_SENSITIVITY   =   0.08f;
const float CAM_FAR_PLANE     = 100.0f;
const float CAM_NEAR_PLANE    =   0.1f;
const glm::vec3 CAM_WORLD_UP  = glm::vec3(0.0f, 1.0f, 0.0f);

const int CAM_MODE_FIRST_PERSON = 1;
const int CAM_MODE_THIRD_PERSON = 3;

const float CAM_DISTANCE_THIRD_PERSON = 3.0f;
const float CAM_HEIGHT_OFFSET_THIRD_PERSON = 1.0f;

// ========================
// ESCENARIO
// ========================
const float HALL_WIDTH = 12.0f;
const float HALL_HEIGHT = 3.0f;
const float HALL_LENGTH = 100.0f;
const float WALL_THICKNESS = 0.15f;
const float COLLISION_MARGIN = 0.3f;

// =========================
// LUZ
// =========================
const float FLASHLIGHT_ON_AMBIENT = 0.04f;        // valor correcto: 0.04
const float FLASHLIGHT_ON_DIFFUSE = 1.1f;         // antes 0.2
const float FLASHLIGHT_ON_SPECULAR = 0.4f;        // antes 0.01
const float FLASHLIGHT_SPECULAR_STRENGTH = 32.0f; // antes 0.5

const float FLASHLIGHT_OFF_AMBIENT = 0.005f;
const float FLASHLIGHT_OFF_DIFFUSE = 0.0f;
const float FLASHLIGHT_OFF_SPECULAR = 0.0f;

const float FLASHLIGHT_INNER_ANGLE = 18.0f;
const float FLASHLIGHT_OUTER_ANGLE = 45.0f;

// =========================
// PERSONAJE
// =========================
const float CHARACTER_INITIAL_Y = 0.3f;

const glm::vec3 HEAD_POSITION = glm::vec3(0.0f, 1.40f, 0.0f);
const glm::vec3 HEAD_SCALE = glm::vec3(0.52f, 0.32f, 0.52f);

const glm::vec3 TORSO_POSITION = glm::vec3(0.0f, 0.85f, 0.0f);
const glm::vec3 TORSO_SCALE = glm::vec3(0.75f, 0.80f, 0.40f);

const glm::vec3 LEFT_ARM_POSITION = glm::vec3(-0.5125f, 0.85f, 0.0f);
const glm::vec3 RIGHT_ARM_POSITION = glm::vec3(0.5125f, 0.85f, 0.0f);
const glm::vec3 ARM_SCALE = glm::vec3(0.22f, 0.80f, 0.35f);

const glm::vec3 LEFT_LEG_POSITION = glm::vec3(-0.22f, 0.10f, 0.0f);
const glm::vec3 RIGHT_LEG_POSITION = glm::vec3(0.22f, 0.10f, 0.0f);
const glm::vec3 LEG_SCALE = glm::vec3(0.28f, 0.90f, 0.35f);
const float LEG_SWING_AMPLITUDE = 25.0f; // grados máximos de oscilación
const float LEG_SWING_SPEED = 8.0f;      // frecuencia en rad/s

const glm::vec3 TP_FLASHLIGHT_POSITION = glm::vec3(0.55f, -0.15f, -0.35f);
const glm::vec3 TP_FLASHLIGHT_POSITION_OFFSET = glm::vec3(0.0f, -0.3f, 0.1f);
const glm::vec3 FLASHLIGHT_SCALE = glm::vec3(0.10f, 0.10f, 0.45f);

const glm::vec3 FP_RIGHT_ARM_OFFSET = glm::vec3(0.45f, -0.65f, 0.35f);
const glm::vec3 FP_FLASHLIGHT_OFFSET = glm::vec3(0.10f, 0.15f, 0.40f);

const unsigned int VERTEX_COUNT = 36; // Número de vértices para un cubo (6 caras * 2 triángulos por cara * 3 vértices por triángulo)


#endif // CONSTANTS_H