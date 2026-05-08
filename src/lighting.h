#ifndef LIGHTING_H
#define LIGHTING_H

#include <glm/glm.hpp>

#include "shader.h"
#include "camera.h"


typedef struct{
    // Vectores de la posición y dirección de la linterna
    glm::vec3 position;
    glm::vec3 direction;

    // Valores de la luz siguiendo el modelo de Phong
    float ambient;
    float diffuse;
    float specular;

    // Valores de los ángulos de la linterna
    float innerAngle; 
    float outerAngle;

    // Valor de la fuerza de la luz especular (shininess)
    float specularStrength;
} FlashLight;

extern FlashLight flashlight;

// =========================
// FUNCIONES
// =========================
void initFlashlight(FlashLight &fl);
void updateFlashlight(FlashLight &fl, const glm::vec3 &position, const glm::vec3 &direction);
void sendFlashlightToShader(const FlashLight &fl, Shader shader, const Camera &cam);

#endif // LIGHTING_H