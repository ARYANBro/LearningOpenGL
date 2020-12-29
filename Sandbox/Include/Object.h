#pragma once

#include "Graphics/Shader.h"
#include "Graphics/Mesh.h"

#include <glm/glm.hpp>

#include <memory>

class Camera;

struct Object
{
public:
    Object(const glm::mat4& transform = glm::mat4(1.0f),
        const std::shared_ptr<Shader>& shader = Shader::Create(),
        const std::shared_ptr<Mesh>& mesh = std::make_shared<Mesh>());

    Object(const Mesh& mesh) noexcept
        : Object(glm::mat4(1.0f), Shader::Create(), std::make_shared<Mesh>(mesh))
    {
    }

    virtual void OnUpdate([[maybe_unused]] const Camera& camera, [[maybe_unused]] const glm::mat4& projectionMatrix) noexcept {}
    virtual void OnRender() noexcept { m_Mesh->Render(); }
    virtual void OnImGuiRender() noexcept {}

    void SetTransform(const glm::mat4& transform) noexcept { m_Transform = transform; }
    void SetShader(const std::shared_ptr<Shader>& shader);

    const glm::mat4& GetTransform() const noexcept { return m_Transform; }
    const std::shared_ptr<Shader>& GetShader() const noexcept { return m_Shader; }
    const Mesh& GetMesh() const noexcept { return *m_Mesh; }

private:
    glm::mat4 m_Transform;
    std::shared_ptr<Shader> m_Shader;
    std::shared_ptr<Mesh> m_Mesh;
};
