#include <GLFW/glfw3.h>

#include "timedata.h"

// =========================
// PÚBLICAS
// =========================
// INICIALIZAR EL TIEMPO
void initTime(TimeData &td)
{
    td.currentTime = glfwGetTime();
    td.lastTime = td.currentTime;
    td.deltaTime = 0.0;
}

// ACTUALIZAR EL TIEMPO
// Cada vez que se actualiza el tiempo:
// - Se recalcula el nuevo tiempo actual
// - Se calcula el lapso de tiempo entre cálculos
// - Se almacena el nuevo tiempo actual como último tiempo observado
// - Se almacena el nuevo tiempo actual como el tiempo actual
void updateTime(TimeData &td)
{
    double newCurrentTime = glfwGetTime();
    td.deltaTime = newCurrentTime - td.lastTime;
    td.lastTime = newCurrentTime;
    td.currentTime = newCurrentTime;
}