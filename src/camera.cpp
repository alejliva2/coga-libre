#include <glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stb_image.h>
#include <glm/gtc/matrix_transform.hpp>

#include "camera.h"
#include "constants.h"

namespace {

}

Camera cam;

// =========================
// PRIVADAS
// =========================

// Actualizamos los vectores necesarios para la cámara a partir de los ángulos Euler
void _updateCameraVectors(Camera &cam) {
    // Calcular el vector front a partir de los ángulos Euler
    glm::vec3 front;
    front.x = cos(glm::radians(cam.yaw)) * cos(glm::radians(cam.pitch));
    front.y = sin(glm::radians(cam.pitch));
    front.z = sin(glm::radians(cam.yaw)) * cos(glm::radians(cam.pitch));
    cam.front = glm::normalize(front);

    // Recalcular los vectores right y up
    glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

    cam.right = glm::normalize(glm::cross(cam.front, worldUp));
    cam.up = glm::normalize(glm::cross(cam.right, cam.front));
}

// =========================
// PÚBLICAS
// =========================

// Inicializamos la cámara con una posición inicial
void initCamera(Camera &cam, glm::vec3 initialPosition) {
    cam.position = initialPosition;
    cam.yaw = -90.0f; // Mirando hacia el eje -Z
    cam.pitch = 0.0f; // Sin inclinación vertical
    cam.up = glm::vec3(0.0f, 1.0f, 0.0f); // Vector hacia arriba

    cam.fov = 60.0f; // Campo de visión
    cam.speed = 1.0f; // Velocidad de movimiento
    cam.sensitivity = 0.01f; // Sensibilidad del ratón
    cam.farPlane = 100.0f; // Plano lejano
    cam.nearPlane = 0.1f; // Plano cercano

    cam.firstMouse = true;

    _updateCameraVectors(cam);
}

// Procesamos la entrada del teclado
void processKeyboard(Camera &cam, GLFWwindow *window, float deltaTime) {
    float distance = cam.speed * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cam.position += cam.front * distance;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cam.position -= cam.front * distance;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cam.position -= cam.right * distance;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cam.position += cam.right * distance;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        return glfwSetWindowShouldClose(window, true);
    

    cam.position.y = HEIGHT_EYE; // Mantener la altura del ojo constante
}

// Procesamos el movimiento del ratón
void processMouseMovement(Camera &cam, float xpos, float ypos) {
    // Inicializamos la posición del ratón en la primera lectura 
    if (cam.firstMouse) {
        cam.lastX = xpos;
        cam.lastY = ypos;
        cam.firstMouse = false;
    }

    // Calculamos el offset del ratón desde la última posición
    float xoffset = (xpos - cam.lastX) * cam.sensitivity;  
    float yoffset = (cam.lastY - ypos) * cam.sensitivity; // invertimos Y para que al mover hacia arriba se suba la pantalla

    cam.yaw += xoffset;
    cam.pitch += yoffset;

    // Limitar el pitch para evitar el efecto de "gimbal lock"
    cam.pitch = glm::clamp(cam.pitch, -89.0f, 89.0f);    

    _updateCameraVectors(cam);
}


void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    (void)window; // no lo usamos, pero GLFW lo exige en la firma
    processMouseMovement(cam, (float)xpos, (float)ypos);
}


glm::mat4 getViewMatrix(const Camera &cam) {
    return glm::lookAt(cam.position, cam.position + cam.front, cam.up);
}


glm::mat4 getProjectionMatrix(const Camera &cam, float aspectRatio  ) {
    return glm::perspective(glm::radians(cam.fov), aspectRatio, cam.nearPlane, cam.farPlane);
}