#include <iostream>

#include <glad.h>
#include <GLFW/glfw3.h>

#include "camera.h"
#include "constants.h"
#include "input.h"
#include "lighting.h"
#include "timedata.h"

// Punteros internos compartidos con el callback:
// - GLFW llama al callback por su cuenta si se pulsa una tecla
// - La firma de la llamada está fijada
// - La llamada no puede acceder a "camera" que vive en el main
// - Solución: guardar su dirección en variables estáticas de archivo
// - En el main, antes del bucle principal:
//   registerInputCallbacks(window, &time, &camera, &flashlight);
static TimeData *g_time = nullptr;
static Camera *g_camera = nullptr;
static Flashlight *g_flashlight = nullptr;

// =========================
// HELPERS
// =========================
// Callback de teclado
static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    (void)scancode;
    (void)mods;

    // Solo reaccionar a pulsaciones
    if (action != GLFW_PRESS)
        return;

    switch (key)
    {
    // Salir del programa
    case GLFW_KEY_ESCAPE:
        glfwSetWindowShouldClose(window, true);
        break;
    // Pantalla completa
    case GLFW_KEY_F11:
    {
        GLFWmonitor *monitor = glfwGetWindowMonitor(window);
        if (monitor == nullptr)
        {
            // De modo Ventana a modo Pantalla Completa
            monitor = glfwGetPrimaryMonitor();
            const GLFWvidmode *mode = glfwGetVideoMode(monitor);
            glfwSetWindowMonitor(window,
                                 monitor,
                                 0,
                                 0,
                                 mode->width,
                                 mode->height,
                                 mode->refreshRate);
        }
        else
        {
            // De modo Pantalla Completa a modo Ventana
            glfwSetWindowMonitor(window,
                                 nullptr,
                                 100,
                                 100,
                                 SCR_WIDTH,
                                 SCR_HEIGHT,
                                 GLFW_DONT_CARE);
        }
        if (g_camera)
            g_camera->firstMouse = true;
        break;
    }
    // Cambiar el modo de la cámara
    case GLFW_KEY_F5:
        if (g_flashlight)
        {
            if (g_camera->mode == CAM_MODE_FIRST_PERSON)
                g_camera->mode = CAM_MODE_THIRD_PERSON;
            else
                g_camera->mode = CAM_MODE_FIRST_PERSON;
        }
        break;
    // Encender/Apagar la linterna
    case GLFW_KEY_F:
        if (g_flashlight)
            toggleFlashlight(*g_flashlight);
        break;
    // Encender/Apagar luces generales
    case GLFW_KEY_L:
        if (g_flashlight)
            toggleDebugLight(*g_flashlight);
        break;
    }
}

// Callback de ratón
static void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    (void)window;
    // Procesar el movimiento del ratón
    processMouseMovement(*g_camera, (float)xpos, (float)ypos);
}

// =========================
// PÚBLICAS
// =========================
// REGISTRAR LOS CALLBACKS
void registerInputCallbacks(GLFWwindow *window, TimeData *time, Camera *camera, Flashlight *flashlight)
{
    // Se igualan punteros globales a objetos que viven en el main
    g_time = time;
    g_camera = camera;
    g_flashlight = flashlight;

    // Registrar los callbacks de teclado y ratón
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    // Capturar y ocultar el cursor para efecto FPS
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

// POLLING CONTINUO: SE LLAMA CADA FRAME DESDE EL BUCLE PRINCIPAL
void processInput(GLFWwindow *window)
{
    // Si el puntero apunta a NULL, salir
    if (g_camera == nullptr)
        return;

    // Calcular la distancia
    float distance = g_camera->speed * g_time->deltaTime;

    // Movimiento WASD clásico
    glm::vec3 flatFront = glm::normalize(glm::vec3(g_camera->front.x, 0.0f, g_camera->front.z));
    glm::vec3 flatRight = glm::normalize(glm::vec3(g_camera->right.x, 0.0f, g_camera->right.z));

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        g_camera->position += flatFront * distance;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        g_camera->position -= flatFront * distance;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        g_camera->position -= flatRight * distance;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        g_camera->position += flatRight * distance;

    // COLISIONES: resulta ser sencillo
    float halfW = HALL_WIDTH / 2.0f - COLLISION_MARGIN;
    float halfL = HALL_LENGTH / 2.0f - COLLISION_MARGIN;
    g_camera->position.x = glm::clamp(g_camera->position.x, -halfW, halfW);
    g_camera->position.z = glm::clamp(g_camera->position.z, -halfL, halfL);

    // Fijar la altura del ojo para el movimiento horizontal
    g_camera->position.y = HEIGHT_EYE;
}