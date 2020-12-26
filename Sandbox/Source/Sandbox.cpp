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
    try
    {
        m_LightShader = Shader::Create("Assets/Shaders/Light.glsl");
        m_Light.SetShader(m_LightShader);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    m_Camera.SetEulerAngles(280.0f, -10.0f);
    m_LightColor = { 1.0f, 1.0f, 1.0f };
    m_LightPosition = { 1.2f, 1.0f, 2.0f };

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

    m_Cube.SetLightColor(m_LightColor);
    m_Cube.SetLightPosition(m_LightPosition);

    m_ProjectionMatrix = glm::perspective(glm::radians(m_Fov), m_AspectRatio, m_ZNear, m_ZFar);
    m_LightPosition.x = std::cos(glfwGetTime());
    m_Camera.Update(delta);
    m_FrameTime = delta;
    m_Cube.OnUpdate(m_Camera, m_ProjectionMatrix);
}

void Sandbox::OnRender() noexcept
{
    m_ModelMatrix = glm::mat4(1.0f);

    m_Cube.OnRender();

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

    ImGui::Begin("Properties");

    if (ImGui::CollapsingHeader("Cube"))
    {
        ImGui::Indent();
        m_Cube.OnImGuiRender();
    }

    ImGui::End();
}
