#pragma once

#include "Object.h"
#include "Graphics/Material.h"
#include "Graphics/Light.h"

#include <glm/glm.hpp>

class CubeObject : public Object
{
public:
    CubeObject() noexcept;
    CubeObject(const Mesh& mesh)
        : Object(mesh)
    {
        SetShader(Shader::Create("Assets/Shaders/Cube.glsl")); 
    }

    CubeObject(const LightProperties& lightProperties, const MaterialProperties& materialProperties);

    virtual void OnUpdate(const Camera& camera, const glm::mat4& projectionMatrix) noexcept override;
    virtual void OnImGuiRender() noexcept override;

    void SetLightProperties(const LightProperties& properties) noexcept { m_LightProps = properties; }
    void SetMaterialProperties(const MaterialProperties& properties) noexcept { m_MaterialProps = properties; }
    void SetPosition(glm::vec3 position) noexcept { m_Position = position; }

    glm::vec3 GetPosition() const noexcept { return m_Position; }
    const MaterialProperties& GetMaterialProperties() const noexcept { return m_MaterialProps; }
    const LightProperties& GetLightProperties() const noexcept { return m_LightProps; }

private:
    glm::vec3 m_Position{ 0.0f };

    MaterialProperties m_MaterialProps = { 
        { 0.0215f, 0.1745f, 0.0215f },
        { 0.07568f, 0.61424f, 0.07568f },
        { 0.633f, 0.727811, 0.633f },
        { 2.0f }
    };

    LightProperties m_LightProps = {
        { 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f }
    };
};
