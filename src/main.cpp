#include <cstdlib>
#include <iostream>

#include <glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera.h"
#include "character.h"
#include "constants.h"
#include "input.h"
#include "scene.h"
#include "shader.h"
#include "textures.h"

// Declaración externa de la función de carga de los shaders
// Esta es la función que usábamos antes
// extern GLuint setShaders(const char *nVertx, const char *nFrag);

// =========================
// REDIMENSIONADO
// =========================
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    (void)window;
    glViewport(0, 0, width, height);
}

// =========================
// INICIALIZACIÓN OPENGL
// =========================
void openGlInit()
{
    // Configuración inicial de OpenGL
    glClearDepth(1.0f); // Valor inicial del z-buffer
    glClearColor(CLEAR_COLOR.r,
                 CLEAR_COLOR.g,
                 CLEAR_COLOR.b,
                 CLEAR_COLOR.a);         // Color de limpieza (negro)
    glEnable(GL_DEPTH_TEST);             // Habilitar test de profundidad
    glEnable(GL_MULTISAMPLE);            // Activar MSAA
    glEnable(GL_BLEND);                  // Activa la mezcla de colores
    glBlendFunc(GL_SRC_ALPHA,            // Configuración estándar del canal alfa
                GL_ONE_MINUS_SRC_ALPHA); //
    // glEnable(GL_CULL_FACE);           // Ocultar caras traseras
    // glCullFace(GL_BACK);              // Especificar que caras ocultar
}

int main()
{
    // =========================
    // 1. Inicializar GLFW
    // =========================
    if (!glfwInit())
    {
        std::cerr << "Error: no se pudo inicializar GLFW\n";
        return EXIT_FAILURE;
    }

    // Establecer versión de OpenGL + antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    // =========================
    // 2. Crear ventana
    // =========================
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Proyecto Libre", NULL, NULL);

    if (window == nullptr)
    {
        std::cerr << "Error: no se pudo crear la ventana GLFW\n";
        glfwTerminate();
        return EXIT_FAILURE;
    }

    // Establecer como contexto actual
    glfwMakeContextCurrent(window);
    // Ajustar swap interval (vsync)
    glfwSwapInterval(1);

    // =========================
    // 3. Inicializar GLAD
    // =========================
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Error: no se pudo inicializar GLAD\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        return EXIT_FAILURE;
    }

    // =========================
    // 4. Configuración OpenGL
    // =========================
    openGlInit();

    // Debug
    std::cout << "\nOpenGL inicializado correctamente.\n";
    std::cout << "Versión: " << glGetString(GL_VERSION) << '\n';
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << '\n';

    // =========================
    // 5. Definiciones
    // =========================
    // Definir e inicializar shaders
    Shader phong = createShader("shaders/phong.vert", "shaders/phong.frag");
    Shader unlit = createShader("shaders/unlit.vert", "shaders/unlit.frag");

    // Definir e inicializar tiempo, cámara y habitación
    TimeData time;
    Camera camera;
    Room room;
    initTime(time);
    initCamera(camera, glm::vec3(0.0f, HEIGHT_EYE, 0.0f));
    initRoom(room, phong.programID);

    // =========================
    // 6. Callbacks
    // =========================
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    registerInputCallbacks(window, &time, &camera);

    // =========================
    // 7. Loop principal
    // =========================
    while (!glfwWindowShouldClose(window))
    {
        // Input
        // processInput(window);

        // Limpieza de profundidad
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Calcular el aspectRatio
        float aspectRatio = (float)SCR_WIDTH / (float)SCR_HEIGHT;

        // Procesar el input
        processInput(window);

        // Matrices de vista y proyección
        glm::mat4 view = getViewMatrix(camera);
        glm::mat4 projection = getProjectionMatrix(camera, aspectRatio);

        // Activar los shaders
        useShader(phong);
        shaderSetMat4(phong, "view", view);
        shaderSetMat4(phong, "projection", projection);
        shaderSetFloat(phong, "slAmbient", 0.2f);

        // Dibujar la escena
        drawRoom(room, phong);

        // Intercambiar buffers y procesar eventos
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Terminar
    glfwTerminate();

    return EXIT_SUCCESS;
}