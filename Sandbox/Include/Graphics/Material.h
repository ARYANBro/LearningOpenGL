#pragma once

#include <glm/glm.hpp>

struct MaterialProperties
{
    glm::vec3 Ambient;
    glm::vec3 Diffuse;
    glm::vec3 Specular;
    float Shininess;
};
