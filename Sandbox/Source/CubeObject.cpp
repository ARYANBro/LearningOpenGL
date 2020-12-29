#include "CubeObject.h"


#include "Camera.h"
#include "Graphics/Meshes/CubeMesh.h"
#include "Graphics/Shader.h"

#include <imgui.h>

#include <memory>
#include <iostream>

CubeObject::CubeObject() noexcept
    : Object(glm::mat4(1.0f), Shader::Create("Assets/Shaders/Cube.glsl"), std::make_shared<CubeMesh>())
{
}

CubeObject::CubeObject(const LightProperties& lightProperties, const MaterialProperties& materialProperties)
    : Object(glm::mat4(1.0f), Shader::Create("Assets/Shaders/Cube.glsl"), std::make_shared<CubeMesh>()), m_Position(),
    m_MaterialProps(materialProperties), m_LightProps(lightProperties)
{
}

void CubeObject::OnUpdate(const Camera& camera, const glm::mat4& projectionMatrix) noexcept
{
    SetTransform(glm::translate(glm::mat4(1.0f), m_Position));

    const auto& shader = GetShader();
    shader->Bind();

    try
    {
        shader->SetFloat3("u_MaterialProps.Ambient", m_MaterialProps.Ambient);
        shader->SetFloat3("u_MaterialProps.Diffuse", m_MaterialProps.Diffuse);
        shader->SetFloat3("u_MaterialProps.Specular", m_MaterialProps.Specular);
        shader->SetFloat("u_MaterialProps.Shininess", m_MaterialProps.Shininess);

        shader->SetFloat3("u_LightPosition", m_LightProps.Position);
        shader->SetFloat3("u_LightProps.Ambient", m_LightProps.Ambient);
        shader->SetFloat3("u_LightProps.Diffuse", m_LightProps.Diffuse);
        shader->SetFloat3("u_LightProps.Specular", m_LightProps.Specular);

        shader->SetMat4("u_ModelMatrix", GetTransform());
        shader->SetMat4("u_ViewMatrix", camera.GetViewMatrix());
        shader->SetMat4("u_ProjectionMatrix", projectionMatrix);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void CubeObject::OnImGuiRender() noexcept
{
    if (ImGui::CollapsingHeader("Material Properties", ImGuiTreeNodeFlags_SpanFullWidth))
    {
        ImGui::ColorEdit3("Ambient", &m_MaterialProps.Ambient.r);
        ImGui::Spacing();

        ImGui::ColorEdit3("Diffuse", &m_MaterialProps.Diffuse.r);
        ImGui::Spacing();

        ImGui::ColorEdit3("Specular", &m_MaterialProps.Specular.r);
        ImGui::SliderFloat("Shininess", &m_MaterialProps.Shininess, 2, 256);
    }

    ImGui::Separator();
    ImGui::Unindent();
    ImGui::DragFloat3("Position", &m_Position.x, 0.1f);
}
