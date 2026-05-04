#include <glad.h>
#include <glm/glm.hpp>

#include "character.h"

void _initCharacter(BodyPart &bodyPart,
                    glm::vec3 position,
                    glm::vec3 scale,
                    glm::vec3 color,
                    float transAngle,
                    float speed,
                    GLuint textureID)
{
    bodyPart.position = position;
    bodyPart.scale = scale;
    bodyPart.color = color;
    bodyPart.transAngle = transAngle;
    bodyPart.speed = speed;
    bodyPart.textureID = textureID;
}