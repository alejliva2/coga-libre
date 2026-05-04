#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>

#include "camera.h"
#include "timedata.h"

// =========================
// INPUT
// =========================
void registerInputCallbacks(GLFWwindow *window, TimeData *time, Camera *camera);
void processInput(GLFWwindow *window);

#endif