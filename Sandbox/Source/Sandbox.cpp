#include "Sandbox.h"

#include "Graphics/VertexBuffer.h"
#include "Graphics/ElementBuffer.h"

#include "DeltaTime.h"
#include "Input.h"

#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <vector>
#include <cassert>
#include <iostream>

void Sandbox::OnBegin() noexcept
{
    m_Camera.SetEulerAngles(280.0f, -10.0f);

    try
    {
        m_CubeShader = Shader::Create("Assets/Shaders/Cube.glsl");
        m_CubeShader->Bind();
        m_CubeShader->SetFloat("u_SpecularStrength", m_SpecularStrength);
        m_CubeShader->SetInt("u_Shininess", m_Shininess);
        m_CubeShader->SetFloat("u_AmbientStrength", m_AmbientStrength);

        m_Cube.SetShader(m_CubeShader);

        m_LightShader = Shader::Create("Assets/Shaders/Light.glsl");
        m_Light.SetShader(m_LightShader);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    m_LightColor = { 1.0f, 1.0f, 1.0f };
    m_LightPosition = { 1.2f, 1.0f, 2.0f };
    m_CubePosition = { 0.0f, 0.0f, 0.0f };

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Sandbox::OnUpdate(DeltaTime delta) noexcept
{
    if (Input::IsKeyPressed(GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(GetWindow().GetHandle(), GLFW_TRUE);
    }

    if (Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_MIDDLE))
    {
        m_Fov = 45.0f;
    }

    m_CubeShader->Bind();

    try
    {
        if (m_DiffuseChecked)
        {
            m_CubeShader->SetBool("u_EnableDiffuse", true);
        }
        else
        {
            m_CubeShader->SetBool("u_EnableDiffuse", false);
        }

        if (m_SpecularChecked)
        {
            m_CubeShader->SetBool("u_EnableSpecular", true);
        }
        else
        {
            m_CubeShader->SetBool("u_EnableSpecular", false);
        }

        if (m_AmbientChecked)
        {
            m_CubeShader->SetBool("u_EnableAmbient", true);
        }
        else
        {
            m_CubeShader->SetBool("u_EnableAmbient", false);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    m_CubeShader->SetFloat("u_SpecularStrength", m_SpecularStrength);
    m_CubeShader->SetInt("u_Shininess", m_Shininess);
    m_CubeShader->SetFloat("u_AmbientStrength", m_AmbientStrength);
    
    m_ProjectionMatrix = glm::perspective(glm::radians(m_Fov), m_AspectRatio, m_ZNear, m_ZFar);
    m_LightPosition.x = std::cos(glfwGetTime());
    m_Camera.Update(delta);
    m_FrameTime = delta;
}

void Sandbox::OnRender() noexcept
{
    m_ModelMatrix = glm::mat4(1.0f);

    m_CubeShader->Bind();

    try
    {
        m_CubeShader->SetFloat3("u_ObjectColor", { 0.3f, 0.9f, 0.4f });
        m_CubeShader->SetFloat3("u_LightColor", m_LightColor);
        m_CubeShader->SetFloat3("u_LightPosition", m_LightPosition);

        m_ModelMatrix = glm::translate(m_ModelMatrix, m_CubePosition);

        m_CubeShader->SetMat4("u_ModelMatrix", m_ModelMatrix);
        m_CubeShader->SetMat4("u_ViewMatrix", m_Camera.GetViewMatrix());
        m_CubeShader->SetMat4("u_ProjectionMatrix", m_ProjectionMatrix);

    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    m_Cube.Render();

    m_ModelMatrix = glm::mat4(1.0f);

    m_ModelMatrix = glm::translate(m_ModelMatrix, m_LightPosition);
    m_ModelMatrix = glm::scale(m_ModelMatrix, glm::vec3(0.2f));

    m_LightShader->Bind();

    try
    {
        m_LightShader->SetFloat3("u_LightColor", m_LightColor);

        m_LightShader->SetMat4("u_ModelMatrix", m_ModelMatrix);
        m_LightShader->SetMat4("u_ViewMatrix", m_Camera.GetViewMatrix());
        m_LightShader->SetMat4("u_ProjectionMatrix", m_ProjectionMatrix);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    m_Light.Render();
}

void Sandbox::OnImGuiRender() noexcept
{
    ImGui::Begin("Stats");
    ImGui::Text("Frametime: %.4gms", m_FrameTime * 1000);
    ImGui::End();

    ImGui::Begin("Properties", nullptr, ImGuiWindowFlags_MenuBar);

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

    ImGui::End();
}
