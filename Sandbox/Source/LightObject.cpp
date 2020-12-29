#include "LightObject.h"

#include "Camera.h"

#include <glfw/glfw3.h>
#include <imgui.h>

#include <iostream>


LightObject::LightObject(const LightProperties& lightProperties, const MaterialProperties& materialProperties)
   :  Object(glm::scale(GetTransform(), glm::vec3(0.2f)), Shader::Create("Assets/Shaders/Light.glsl"), std::make_shared<CubeMesh>())
{
    m_Props = lightProperties;
    m_MaterialProps = materialProperties;
}

LightObject::LightObject()
    : LightObject({}, {})
{
}

void LightObject::OnUpdate(const Camera& camera, const glm::mat4& projectionMatrix) noexcept
{
    SetTransform(glm::translate(static_cast<glm::mat4>(static_cast<glm::mat3>(GetTransform())), m_Props.Position));
    const auto& shader = GetShader();
    shader->Bind();

    try
    {
        shader->SetMat4("u_ModelMatrix", GetTransform());
        shader->SetMat4("u_ViewMatrix", camera.GetViewMatrix());
        shader->SetMat4("u_ProjectionMatrix", projectionMatrix);
        shader->SetFloat4("u_Color", glm::vec4(m_MaterialProps.Diffuse, 1.0f));
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void LightObject::OnImGuiRender() noexcept
{
    ImGui::Separator();
    ImGui::Unindent();
    ImGui::DragFloat3("Light Position", &m_Props.Position.x, 0.1f);
    ImGui::ColorEdit3("Light Color", &m_MaterialProps.Diffuse.r);
}

LightProperties LightObject::GetProperties() const noexcept
{
    return { 
        { m_Props.Position },
        { m_Props.Ambient * m_MaterialProps.Diffuse },
        { m_Props.Diffuse * m_MaterialProps.Diffuse },
        { m_Props.Specular * m_MaterialProps.Diffuse }
    };
}
