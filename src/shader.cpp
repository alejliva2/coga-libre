#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "constants.h"
#include "shader.h"

// =========================
// HELPERS
// =========================
namespace
{
    std::string _readFile(const char* path)
    {
        // 1. Se abre el archivo ubicado en "path"
        // 2. Se crea un flujo de datos en memoria
        // 3. Vuelca todo el contenido del archivo
        // 4. Convierte el contenido en string y lo devuelve
        std::ifstream file(path);
        std::stringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }

    unsigned int _compileShaders(const char* code, unsigned int type)
    {
        // Crear y compilar los shaders
        unsigned int id = glCreateShader(type);
        glShaderSource(id, 1, &code, NULL);
        glCompileShader(id);

        // Comprobar errores de compilación
        int success;
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        // Si la compilación falla
        if (!success)
        {
            // Se escribe el error en el log
            char log[LOG_SIZE];
            glGetShaderInfoLog(id, LOG_SIZE, NULL, log);
            std::cerr << "\nError compilando shader: " << log << std::endl;
        }

        return id;
    }
}; // namespace

// =========================
// PÚBLICAS
// =========================
// LEER, COMPILAR Y ENLAZAR SHADERS
Shader createShader(const char *vertPath, const char *fragPath)
{
    // Leer archivos
    std::string vertCode = _readFile(vertPath);
    std::string fragCode = _readFile(fragPath);

    // Compilar shaders
    unsigned int vs = _compileShaders(vertCode.c_str(), GL_VERTEX_SHADER);
    unsigned int fs = _compileShaders(fragCode.c_str(), GL_FRAGMENT_SHADER);

    // Crear y enlazar el programa
    Shader shader;
    shader.programID = glCreateProgram();
    glAttachShader(shader.programID, vs);
    glAttachShader(shader.programID, fs);
    glLinkProgram(shader.programID);

    // Comprobar errores de enlazado
    int success;
    glGetProgramiv(shader.programID, GL_LINK_STATUS, &success);
    // Si el enlazado falla
    if (!success)
    {
        // Se escribe el error en el log
        char log[LOG_SIZE];
        glGetProgramInfoLog(shader.programID, LOG_SIZE, NULL, log);
        std::cerr << "\nError enlazando programa: " << log << std::endl;
    }

    // Los shaders individuales ya no hacen falta
    glDeleteShader(vs);
    glDeleteShader(fs);

    return shader;
}

// USAR SHADER
void useShader(Shader shader)
{
    glUseProgram(shader.programID);
}

// ENVIAR UN INT AL SHADER
void shaderSetInt(Shader shader, const char* name, int value)
{
    glUniform1i(glGetUniformLocation(shader.programID, name), value);
}

// ENVIAR UN FLOAT AL SHADER
void shaderSetFloat(Shader shader, const char *name, float value)
{
    glUniform1f(glGetUniformLocation(shader.programID, name), value);
}

// ENVIAR UN VEC3 AL SHADER
void shaderSetVec3(Shader shader, const char *name, glm::vec3 value)
{
    glUniform3fv(glGetUniformLocation(shader.programID, name), 1, glm::value_ptr(value));
}

// ENVIAR UN MAT4 AL SHADER
void shaderSetMat4(Shader shader, const char *name, glm::mat4 value)
{
    glUniformMatrix4fv(glGetUniformLocation(shader.programID, name), 1, GL_FALSE, glm::value_ptr(value));
}