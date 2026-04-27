#ifndef CHARACTER_H
#define CHARACTER_H

typedef struct
{
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 color;
    float transAngle;
    float speed;
    unsigned int VAO;
    unsigned int VBO;
    unsigned int vertexCount;
    GLuint textureID;
} Body;



#endif // CHARACTER_H