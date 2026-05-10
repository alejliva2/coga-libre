#include <glm/glm.hpp>

#include "lighting.h"
#include "camera.h"
#include "constants.h"

// =========================
// PÚBLICAS
// =========================
// INICIALIZAR LINTERA
void initFlashlight(Flashlight &flashlight)
{
    flashlight.position = glm::vec3(0.0f, HEIGHT_EYE, 0.0f);
    flashlight.direction = glm::vec3(0.0f, 0.0f, -1.0f);
    flashlight.ambient = FLASHLIGHT_NORMAL_AMBIENT;
    flashlight.diffuse = FLASHLIGHT_ON_DIFFUSE;
    flashlight.specular = FLASHLIGHT_ON_SPECULAR;
    flashlight.specularStrength = FLASHLIGHT_SPECULAR_STRENGTH;
    flashlight.innerAngle = FLASHLIGHT_INNER_ANGLE;
    flashlight.outerAngle = FLASHLIGHT_OUTER_ANGLE;
    flashlight.isOn = true;
    flashlight.debugLight = false;
}

// ACTUALIZAR POSICIÓN Y DIRECCIÓN DE LA LINTERNA
void updateFlashlight(Flashlight &flashlight, const glm::vec3 &position, const glm::vec3 &direction)
{
    flashlight.position = position;
    flashlight.direction = direction;
}

// ENCENDER/APAGAR LA LINTERNA
void toggleFlashlight(Flashlight &flashlight)
{
    flashlight.isOn = !flashlight.isOn;
}

// ENCENDER/APAGAR LUCES GENERALES
void toggleDebugLight(Flashlight &flashlight)
{
    flashlight.debugLight = !flashlight.debugLight;

    if (flashlight.debugLight)
        flashlight.ambient = FLASHLIGHT_DEBUG_AMBIENT;
    else
        flashlight.ambient = FLASHLIGHT_NORMAL_AMBIENT;
}

// ENVIAR PARÁMETROS DE LA LINTERNA AL SHADER
void sendFlashlightToShader(const Flashlight &flashlight, Shader shader, const Camera &cam)
{
    shaderSetVec3(shader, "slPos", flashlight.position);
    shaderSetVec3(shader, "slDir", flashlight.direction);
    shaderSetVec3(shader, "camPos", cam.position);

    if (flashlight.isOn)
    {
        shaderSetFloat(shader, "slAmbient", flashlight.ambient);
        shaderSetFloat(shader, "slDiffuse", flashlight.diffuse);
        shaderSetFloat(shader, "slSpecular", flashlight.specular);
    }
    else
    {
        shaderSetFloat(shader, "slAmbient", FLASHLIGHT_OFF_AMBIENT);
        shaderSetFloat(shader, "slDiffuse", FLASHLIGHT_OFF_DIFFUSE);
        shaderSetFloat(shader, "slSpecular", FLASHLIGHT_OFF_SPECULAR);
    }
    
    shaderSetFloat(shader, "inAngle", glm::cos(glm::radians(flashlight.innerAngle)));
    shaderSetFloat(shader, "extAngle", glm::cos(glm::radians(flashlight.outerAngle)));
    shaderSetFloat(shader, "specularStrength", flashlight.specularStrength);
}
