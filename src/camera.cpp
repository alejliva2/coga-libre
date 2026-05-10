#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "camera.h"
#include "constants.h"

namespace
{
    // =========================
    // HELPERS
    // =========================
    // Actualizar los vectores necesarios para la cámara a partir de los ángulos Euler
    void _updateCameraVectors(Camera &cam)
    {
        // Calcular el vector front a partir de los ángulos Euler
        glm::vec3 front;
        front.x = cos(glm::radians(cam.yaw)) * cos(glm::radians(cam.pitch));
        front.y = sin(glm::radians(cam.pitch));
        front.z = sin(glm::radians(cam.yaw)) * cos(glm::radians(cam.pitch));
        cam.front = glm::normalize(front);

        // Recalcular los vectores right y up
        glm::vec3 worldUp = CAM_WORLD_UP;

        cam.right = glm::normalize(glm::cross(cam.front, worldUp));
        cam.up = glm::normalize(glm::cross(cam.right, cam.front));
    }
}

// =========================
// PÚBLICAS
// =========================
// INICIALIZACIÓN DE LA CÁMARA
void initCamera(Camera &cam, glm::vec3 initialPosition)
{
    cam.position = initialPosition;
    cam.yaw = CAM_INITIAL_YAW;
    cam.pitch = CAM_INITIAL_PITCH;
    cam.up = CAM_WORLD_UP;

    cam.fov = CAM_FOV;
    cam.speed = CAM_SPEED;
    cam.sensitivity = CAM_SENSITIVITY;
    cam.farPlane = CAM_FAR_PLANE;
    cam.nearPlane = CAM_NEAR_PLANE;

    cam.firstMouse = true;

    cam.mode = CAM_MODE_FIRST_PERSON; // modo primera persona por defecto

    _updateCameraVectors(cam);
}

// PROCESAR EL MOVIMIENTO DEL RATÓN
// Esta función vive en camera.cpp porque es lógica pura de cámara
void processMouseMovement(Camera &cam, float xpos, float ypos)
{
    // Inicializar la posición del ratón en la primera lectura
    if (cam.firstMouse)
    {
        cam.lastX = xpos;
        cam.lastY = ypos;
        cam.firstMouse = false;
    }

    // Calcular el offset del ratón desde la última posición
    float xoffset = (xpos - cam.lastX) * cam.sensitivity;
    float yoffset = (cam.lastY - ypos) * cam.sensitivity; // invertimos Y para que al mover hacia arriba se suba la pantalla

    cam.yaw += xoffset;
    cam.pitch += yoffset;

    // Limitar el pitch para evitar el efecto de "gimbal lock"
    cam.pitch = glm::clamp(cam.pitch, -89.0f, 89.0f);

    cam.lastX = xpos;
    cam.lastY = ypos;

    _updateCameraVectors(cam);
}

// OBTENER LA MATRIZ DE VISTA
glm::mat4 getViewMatrix(const Camera &cam)
{
    if (cam.mode == CAM_MODE_FIRST_PERSON)
    {
        // Primera persona: cámara en el ojo, mirando hacia la dirección front
        return glm::lookAt(
            cam.position,
            cam.position + cam.front,
            cam.up);
    }
    else
    {
        // Tercera persona
        // Colocar la cámara detrás del personaje (la posición del personaje es cam.position)
        float distance = CAM_DISTANCE_THIRD_PERSON;
        float heightOffset = CAM_HEIGHT_OFFSET_THIRD_PERSON;
        glm::vec3 cameraPos = cam.position - cam.front * distance + cam.up * heightOffset;

        // Clamp para que no salga de los límites del pasillo (roto)
        /*
        float halfW = HALL_WIDTH / 2.0f - COLLISION_MARGIN;
        float halfL = HALL_LENGTH / 2.0f - COLLISION_MARGIN;
        cameraPos.x = glm::clamp(cameraPos.x, -halfW, -halfW);
        cameraPos.z = glm::clamp(cameraPos.z, -halfL, -halfL);
        */

        // Mirar hacia el personaje
        return glm::lookAt(
            cameraPos,
            cam.position,
            cam.up);
    }
}

// OBTENER LA MATRIZ DE PROYECCIÓN
glm::mat4 getProjectionMatrix(const Camera &cam, float aspectRatio)
{
    return glm::perspective(glm::radians(cam.fov),
                            aspectRatio,
                            cam.nearPlane,
                            cam.farPlane);
}