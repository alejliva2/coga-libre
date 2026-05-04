#include <glad.h>
#include <GLFW/glfw3.h>

#include "camera.h"
#include "constants.h"
#include "input.h"
#include "timedata.h"

// Punteros internos compartidos con el callback:
// - GLFW llama al callback por su cuenta si se pulsa una tecla
// - La firma de la llamada está fijada
// - La llamada no puede acceder a "camera" que vive en el main
// - Solución: guardar su dirección en variables estáticas de archivo
// - En el main, antes del bucle principal:
//   registerInputCallbacks(window, &time, &camera);
static TimeData *g_time = nullptr;
static Camera *g_camera = nullptr;

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

        // TODO añadir más teclas
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
void registerInputCallbacks(GLFWwindow *window, TimeData *time, Camera *camera)
{
    // Se igualan punteros globales a objetos que viven en el main
    g_time = time;
    g_camera = camera;

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
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        g_camera->position += g_camera->front * distance;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        g_camera->position -= g_camera->front * distance;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        g_camera->position -= g_camera->right * distance;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        g_camera->position += g_camera->right * distance;

    // Fijar la altura del ojo para el movimiento horizontal
    g_camera->position.y = HEIGHT_EYE;
}