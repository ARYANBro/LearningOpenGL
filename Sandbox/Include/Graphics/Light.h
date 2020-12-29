#pragma once

#include <glm/glm.hpp>

struct LightProperties
{
    glm::vec3 Position;
    glm::vec3 Ambient;
    glm::vec3 Diffuse;
    glm::vec3 Specular;
};
