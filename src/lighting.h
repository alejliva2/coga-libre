#ifndef LIGHTING_H
#define LIGHTING_H

#include <glm/glm.hpp>

#include "shader.h"
#include "camera.h"

struct Flashlight
{
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
    // Está encendida/apagada
    bool isOn;
    // Luz general (debug útil para corrección final)
    bool debugLight;
};

void initFlashlight(Flashlight &flashlight);
void updateFlashlight(Flashlight &flashlight, const glm::vec3 &position, const glm::vec3 &direction);
void toggleFlashlight(Flashlight &flashlight);
void toggleDebugLight(Flashlight &flashlight);
void sendFlashlightToShader(const Flashlight &flashlight, Shader shader, const Camera &camera);

#endif // LIGHTING_H