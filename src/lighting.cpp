#include <glm/gtc/matrix_transform.hpp>

#include "lighting.h"
#include "camera.h"
#include "constants.h"

FlashLight flashlight;

// Inicializamos la linterna con los valores por defecto
void initFlashlight(FlashLight &fl)
{
    fl.position = glm::vec3(0.0f, HEIGHT_EYE, 0.0f);
    fl.direction = glm::vec3(0.0f, 0.0f, -1.0f);

    fl.ambient = FLASHLIGHT_AMBIENT;
    fl.diffuse = FLASHLIGHT_DIFFUSE;
    fl.specular = FLASHLIGHT_SPECULAR;
    fl.specularStrength = FLASHLIGHT_SPECULAR_STRENGTH;

    fl.innerAngle = FLASHLIGHT_INNER_ANGLE;
    fl.outerAngle = FLASHLIGHT_OUTER_ANGLE;
}

// Actualizamos la posición y dirección de la linterna
void updateFlashlight(FlashLight &fl, const glm::vec3 &position, const glm::vec3 &direction)
{
    fl.position = position;
    fl.direction = direction;
}

// Mandamos los parámetros de la linterna al shader
void sendFlashlightToShader(const FlashLight &fl, Shader shader, const Camera &cam)
{
    shaderSetVec3(shader, "slPos", fl.position);
    shaderSetVec3(shader, "slDir", fl.direction);
    shaderSetVec3(shader, "camPos", cam.position);

    shaderSetFloat(shader, "slAmbient", fl.ambient);
    shaderSetFloat(shader, "slDiffuse", fl.diffuse);
    shaderSetFloat(shader, "slSpecular", fl.specular);
    
    shaderSetFloat(shader, "inAngle", glm::cos(glm::radians(fl.innerAngle)));
    shaderSetFloat(shader, "extAngle", glm::cos(glm::radians(fl.outerAngle)));
    shaderSetFloat(shader, "specularStrength", fl.specularStrength);
    
}
