#pragma once

#include "Object.h"
#include "CubeObject.h"
#include "Graphics/Meshes/CubeMesh.h"
#include "Graphics/Light.h"

class LightObject : public Object
{
public:
    LightObject();
    LightObject(const Mesh& mesh)
        : Object(mesh)
    {
        SetShader(Shader::Create("Assets/Shaders/Light.glsl"));
        SetTransform(glm::scale(GetTransform(), glm::vec3(0.2f)));
    }

    LightObject(const LightProperties& lightProperties, const MaterialProperties& materialProperties);

    virtual void OnUpdate(const Camera& camera, const glm::mat4& projectionMatrix) noexcept override;
    virtual void OnImGuiRender() noexcept override;

    const MaterialProperties& GetMaterialProperties() const noexcept { return m_MaterialProps; }
    LightProperties GetProperties() const noexcept;

private:
    LightProperties m_Props{
        { 3.7f, 4.7f, 4.6f },
        { 1.0f, 1.0f, 1.0f },
        { 1.0f, 1.0f, 1.0f },
        { 1.0f, 1.0f, 1.0f }
    };

    MaterialProperties m_MaterialProps{ 
        { 1.0f, 1.0f, 1.0f },
        { 1.0f, 1.0f, 1.0f },
        { 1.0f, 1.0f, 1.0f },
        1.0f
    };
};
