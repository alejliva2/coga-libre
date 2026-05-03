#ifndef CAMERA_H
#define CAMERA_H

typedef struct
{
    // -- Posición y orientación de la cámara --
    glm::vec3 position;  // punto del ojo en el espacio
    glm::vec3 front;   // dirección hacia donde mira la cámara
    glm::vec3 up;      // vector hacia arriba (0,1,0)
    glm::vec3 right;   // vector hacia la derecha (calculado como cross(front, up))e

    // -- Ángulos Euler (calcular front según el ratón) -- 
    float yaw;         // rotación eje Y (izquierda/derecha)
    float pitch;       // rotación eje X (arriba/abajo)

    // -- Configuración de movimiento --
    float fov;        // campo de visión (field of view) para la perspectiva
    float nearPlane;   // plano cercano para la perspectiva 
    float farPlane;    // plano lejano para la perspectiva
    float speed;       // velocidad de movimiento
    float sensitivity; // sensibilidad del ratón

    // -- Estado Ratón --
    bool firstMouse;   // para evitar saltos en la primera lectura del ratón
    float lastX;      // última posición X del ratón
    float lastY;      // última posición Y del ratón
} Camera;

// =========================
// VARIABLES GLOBALES
// =========================
extern Camera cam;


// =========================
// FUNCIONES 
// =========================
void initCamera(Camera &cam, glm::vec3 initialPosition);
void processKeyboard(Camera &cam, GLFWwindow *window, float deltaTime);
void processMouseMovement(Camera &cam, float xpos, float ypos);
glm::mat4 getViewMatrix(const Camera &cam);
glm::mat4 getProjectionMatrix(const Camera &cam, float aspectRatio);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

#endif // CAMERA_H