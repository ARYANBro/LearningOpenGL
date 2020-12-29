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

    m_Emerald.SetPosition({-1.5f, 0.0f, 0.0f});

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

    m_ProjectionMatrix = glm::perspective(glm::radians(m_Fov), m_AspectRatio, m_ZNear, m_ZFar);
    m_Camera.OnUpdate(delta);
    m_Light.OnUpdate(m_Camera, m_ProjectionMatrix);
    
    m_Emerald.SetLightProperties(m_Light.GetProperties());
    m_Emerald.OnUpdate(m_Camera, m_ProjectionMatrix);

    m_Jade.SetLightProperties(m_Light.GetProperties());
    m_Jade.OnUpdate(m_Camera, m_ProjectionMatrix);

    m_FrameTime = delta;
}

void Sandbox::OnRender() noexcept
{
    m_Emerald.OnRender();
    m_Jade.OnRender();
    m_Light.OnRender();
}

void Sandbox::OnImGuiRender() noexcept
{
    ImGui::Begin("Stats");
    ImGui::Text("Frametime: %.4gms", m_FrameTime * 1000);
    ImGui::End();

    ImGui::Begin("Properties");
    AddObjectProperties("Cube", m_Emerald);
    AddObjectProperties("Light", m_Light);
    ImGui::End();
}

void Sandbox::AddObjectProperties(const std::string& name, Object& object) noexcept
{
    if (ImGui::CollapsingHeader(name.c_str()))
    {
        ImGui::Indent();
        object.OnImGuiRender();
    }
}
