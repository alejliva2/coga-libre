#ifndef CAMERA_H
#define CAMERA_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// =========================
// CÁMARA
// =========================
typedef struct
{
    // -- Posición y orientación de la cámara --
    glm::vec3 position; // Punto del ojo en el espacio
    glm::vec3 front;    // Dirección hacia donde mira la cámara
    glm::vec3 up;       // Vector hacia arriba (0,1,0)
    glm::vec3 right;    // Vector hacia la derecha (calculado como cross(front, up))

    // -- Ángulos Euler (calcular front según el ratón) -- 
    float yaw;          // Rotación eje Y (izquierda/derecha)
    float pitch;        // Rotación eje X (arriba/abajo)

    // -- Configuración de movimiento --
    float fov;          // Campo de visión (Field of View) para la perspectiva
    float nearPlane;    // Plano cercano para la perspectiva 
    float farPlane;     // Plano lejano para la perspectiva
    float speed;        // Velocidad de movimiento
    float sensitivity;  // Sensibilidad del ratón

    // -- Estado Ratón --
    bool firstMouse;    // Para evitar saltos en la primera lectura del ratón
    float lastX;        // Última posición X del ratón
    float lastY;        // Última posición Y del ratón
} Camera;


extern Camera cam;

void initCamera(Camera &cam, glm::vec3 initialPosition);
void processMouseMovement(Camera &cam, float xpos, float ypos);
glm::mat4 getViewMatrix(const Camera &cam);
glm::mat4 getProjectionMatrix(const Camera &cam, float aspectRatio);

#endif // CAMERA_H