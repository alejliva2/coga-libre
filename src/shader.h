#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <glm/glm.hpp>

// =========================
// SHADERS
// =========================
typedef struct {
    unsigned int programID;
} Shader;

Shader createShader(const char* vertPath, const char* fragPath);
void useShader(Shader shader);
void shaderSetInt(Shader shader, const char* name, int value);
void shaderSetFloat(Shader shader, const char* name, float value);
void shaderSetVec3(Shader shader, const char* name, glm::vec3 value);
void shaderSetMat4(Shader shader, const char* name, glm::mat4 value);

#endif // SHADER_H