#include "Object.h"

Object::Object(const glm::mat4& transform, const std::shared_ptr<Shader>& shader, const std::shared_ptr<Mesh>& mesh)
    : m_Transform(transform), m_Shader(shader), m_Mesh(mesh)
{
    m_Mesh->SetShader(m_Shader);
}

void Object::SetShader(const std::shared_ptr<Shader>& shader)
{
    m_Shader = shader;
    m_Mesh->SetShader(m_Shader);
}
