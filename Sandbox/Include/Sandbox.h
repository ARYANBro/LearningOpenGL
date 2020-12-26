#pragma once

#include "Application.h"

#include "Graphics/Shader.h"
#include "Graphics/Meshes/CubeMesh.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <imgui.h>

#include <array>
#include <iostream>

struct Object
{
public:
    Object(const glm::mat4& transform = glm::mat4(1.0f),
        const std::shared_ptr<Shader>& shader = Shader::Create(),
        const std::shared_ptr<Mesh>& mesh = std::make_shared<Mesh>())
        : m_Transform(transform), m_Shader(shader), m_Mesh(mesh)
    {
        m_Mesh->SetShader(m_Shader);
    }

    virtual void OnUpdate([[maybe_unused]] const Camera& camera, [[maybe_unused]] const glm::mat4& projectionMatrix) {}
    virtual void OnRender() noexcept
    {
        m_Mesh->Render();
    }

    virtual void OnImGuiRender() noexcept {}

    void SetTransform(const glm::mat4& transform) noexcept { m_Transform = transform; }
    void SetShader(const std::shared_ptr<Shader>& shader) noexcept
    {
        m_Shader = shader;
        m_Mesh->SetShader(m_Shader);
    }

    const glm::mat4& GetTransform() const noexcept { return m_Transform; }
    const std::shared_ptr<Shader>& GetShader() const noexcept { return m_Shader; }
    const Mesh& GetMesh() const noexcept { return *m_Mesh; }

private:
    glm::mat4 m_Transform;
    std::shared_ptr<Shader> m_Shader;
    std::shared_ptr<Mesh> m_Mesh;
};

class CubeObject : public Object
{
public:
    CubeObject(const glm::vec3& lightColor = glm::vec3{ 1.0f }, const glm::vec3& lightPosition = glm::vec3{ 0.0f })
        : Object(glm::mat4(1.0f), Shader::Create("Assets/Shaders/Cube.glsl"), std::make_shared<CubeMesh>())
    {
        m_LightColor = lightColor;
        m_LightPosition = lightPosition;
        GetShader()->Bind();
        GetShader()->SetFloat3("u_ObjectColor", { 0.3f, 0.9f, 0.4f });
    }

    virtual void OnUpdate(const Camera& camera, const glm::mat4& projectionMatrix) override
    {   
        const auto& shader = GetShader();
        shader->Bind();

        try
        {
            if (m_DiffuseChecked)
            {
                shader->SetBool("u_EnableDiffuse", true);
            }
            else
            {
                shader->SetBool("u_EnableDiffuse", false);
            }

            if (m_SpecularChecked)
            {
                shader->SetBool("u_EnableSpecular", true);
            }
            else
            {
                shader->SetBool("u_EnableSpecular", false);
            }

            if (m_AmbientChecked)
            {
                shader->SetBool("u_EnableAmbient", true);
            }
            else
            {
                shader->SetBool("u_EnableAmbient", false);
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }

        SetTransform(glm::translate(GetTransform(), m_Position));
        UpdateUniforms(camera, projectionMatrix);
    }

    virtual void OnImGuiRender() noexcept override
    {
        if (ImGui::CollapsingHeader("Rendering Options"))
        {
            ImGui::Checkbox("Diffuse", &m_DiffuseChecked);
            ImGui::Checkbox("Specular", &m_SpecularChecked);

            if (m_SpecularChecked)
            {
                ImGui::SliderFloat("Specular Strength", &m_SpecularStrength, 0.0f, 1.0f, nullptr, 1.0f);
                ImGui::SliderInt("Shininess", &m_Shininess, 2, 256);
            }

            ImGui::Checkbox("Ambient", &m_AmbientChecked);

            if (m_AmbientChecked)
            {
                ImGui::SliderFloat("Ambient Strength", &m_AmbientStrength, 0.0f, 0.5f, nullptr, 1.0f);
            }
        }
    }

    void SetLightColor(const glm::vec3& color) noexcept { m_LightColor = color; }
    void SetLightPosition(const glm::vec3& position) noexcept { m_LightPosition = position; }

    glm::vec3 GetPosition() const noexcept { return m_Position; }
    float GetSpecularStrength() const noexcept { return m_SpecularStrength; }
    float GetShininess() const noexcept { return m_Shininess; }
    float GetAmbientStrength() const noexcept { return m_AmbientStrength; }

private:
    glm::vec3 m_Position;

    glm::vec3 m_LightColor;
    glm::vec3 m_LightPosition;

    float m_SpecularStrength = 0.1f;
    int m_Shininess = 32;
    float m_AmbientStrength = 0.1f;

    bool m_SpecularChecked = true;
    bool m_AmbientChecked = true;
    bool m_DiffuseChecked = true;

private:
    void UpdateUniforms(const Camera& camera, const glm::mat4& pojectionMatrix) const noexcept
    {
        const auto& shader = GetShader();
        shader->Bind();
        try
        {
            shader->SetFloat3("u_ObjectColor", { 0.3f, 0.9f, 0.4f });
            shader->SetFloat3("u_LightColor", m_LightColor);
            shader->SetFloat3("u_LightPosition", m_LightPosition);

            shader->SetFloat("u_SpecularStrength", m_SpecularStrength);
            shader->SetInt("u_Shininess", m_Shininess);
            shader->SetFloat("u_AmbientStrength", m_AmbientStrength);

            shader->SetMat4("u_ModelMatrix", GetTransform());
            shader->SetMat4("u_ViewMatrix", camera.GetViewMatrix());
            shader->SetMat4("u_ProjectionMatrix", pojectionMatrix);
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
};

class Sandbox : public Application
{    
public:
    Sandbox(std::uint_fast32_t windowWidth, std::uint_fast32_t windowHeight) noexcept
        : Application(windowWidth, windowHeight, "Sandbox")
    {
    }

    virtual void OnBegin() noexcept override;
    virtual void OnUpdate(DeltaTime delta) noexcept override;
    virtual void OnRender() noexcept override;
    virtual void OnImGuiRender() noexcept override;

private:
#if false
    CubeMesh m_Cube;
    glm::vec3 m_CubePosition;
    float m_SpecularStrength = 0.1f;
    int m_Shininess = 32;
    float m_AmbientStrength = 0.1;
    std::shared_ptr<Shader> m_CubeShader;
#endif
    CubeObject m_Cube;
    CubeMesh m_Light = Mesh::Share<CubeMesh>(static_cast<const CubeMesh&>(m_Cube.GetMesh()));

    glm::vec3 m_LightPosition;
    glm::vec3 m_LightColor;

    std::shared_ptr<Shader> m_LightShader;

    glm::mat4 m_ModelMatrix = glm::mat4(1.0f);

    glm::mat4 m_ProjectionMatrix = glm::perspective(glm::radians(m_Fov), m_AspectRatio, m_ZNear, m_ZFar);
    float m_Fov = 45.0f;
    const float m_AspectRatio = static_cast<float>(GetWindow().GetWidth()) / GetWindow().GetHeight();
    const float m_ZNear = 0.1f;
    const float m_ZFar = 1000.0f;

    Camera m_Camera{{ -0.5f, 1.5f, 5.0f }, 2.0f, 8.0f };

    bool m_SpecularChecked = true;
    bool m_AmbientChecked = true;
    bool m_DiffuseChecked = true;

    float m_FrameTime;
};
