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

// ========================
// ESCENARIO
// ========================
const float ROOM_WIDTH  = 15.0f;
const float ROOM_HEIGHT = 6.0f;
const float ROOM_DEPTH  = 15.0f;
const float WALL_THICKNESS = 0.1f;

const glm::vec3 FLOOR_COLOR   = glm::vec3(0.6f, 0.45f, 0.3f);  // madera
const glm::vec3 CEILING_COLOR = glm::vec3(0.9f, 0.9f, 0.9f);   // blanco
const glm::vec3 WALL_COLOR    = glm::vec3(0.8f, 0.75f, 0.7f);  // beige 


#endif // CONSTANTS_H