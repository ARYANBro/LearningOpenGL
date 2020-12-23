#include "OpenGLApplication.h"

#include "Graphics/VertexBuffer.h"
#include "Graphics/ElementBuffer.h"

#include "DeltaTime.h"
#include "Input.h"

#include "GLFW/glfw3.h"
#include "stb_image.h"

#include <vector>
#include <cassert>
#include <iostream>

void OpenGLApplication::OnBegin() noexcept
{
    Input::BindAction("MiddleMouseButtonPressed", [this]()
    {
        return glfwGetMouseButton(GetWindow().GetHandle(), GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS;
    });

    m_Camera.SetPosition(glm::vec3(-0.5f, 1.0f, 4.0f));
    m_Camera.SetEulerAngles(280.0f, -10.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Input::BindKey("Quit", GLFW_KEY_ESCAPE);

    m_LightPosition = glm::vec3(1.2f, 1.0f, 2.0f);

    m_CubeShader = std::make_shared<Shader>("Assets/Shaders/Cube.glsl");
    m_Cube.SetShader(m_CubeShader);

    m_LightShader = std::make_shared<Shader>("Assets/Shaders/Light.glsl");
    m_Light.SetShader(m_LightShader);

    m_LightColor = glm::vec3(1.0f);
}

void OpenGLApplication::OnUpdate(DeltaTime delta) noexcept
{
    if (Input::IsKeyPressed("Quit"))
    {
        glfwSetWindowShouldClose(GetWindow().GetHandle(), true);
    }

    if (Input::IsActionTriggered("MiddleMouseButtonPressed"))
    {
        m_Fov = 45.0f;
    }

    m_ProjectionMatrix = glm::perspective(glm::radians(m_Fov), m_AspectRatio, m_ZNear, m_ZFar);
    m_Camera.Update(delta);
}

void OpenGLApplication::OnRender() noexcept
{
    glClearColor(0.02f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_ModelMatrix = glm::mat4(1.0f);

    m_CubeShader->Bind();
    m_CubeShader->SetFloat3("u_ObjectColor", { 1.0f, 0.4f, 0.4f });
    m_CubeShader->SetFloat3("u_LightColor", m_LightColor);

    m_CubeShader->SetMat4("u_ModelMatrix", m_ModelMatrix);
    m_CubeShader->SetMat4("u_ViewMatrix", m_Camera.GetViewMatrix());
    m_CubeShader->SetMat4("u_ProjectionMatrix", m_ProjectionMatrix);

    m_Cube.Render();

    m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(m_LightPosition));
    m_ModelMatrix = glm::scale(m_ModelMatrix, glm::vec3(0.2f));

    m_LightShader->Bind();
    m_LightShader->SetFloat3("u_LightColor", m_LightColor);

    m_LightShader->SetMat4("u_ModelMatrix", m_ModelMatrix);
    m_LightShader->SetMat4("u_ViewMatrix", m_Camera.GetViewMatrix());
    m_LightShader->SetMat4("u_ProjectionMatrix", m_ProjectionMatrix);

    m_Light.Render();
    
    glfwSwapBuffers(GetWindow().GetHandle());
    GetWindow().PollEvents();
}

void OpenGLApplication::OnMouseMoved(double xPos, double yPos) noexcept
{
    m_Camera.OnMouseMoved(xPos, yPos);
}

void OpenGLApplication::OnMouseScrolled([[maybe_unused]] double xOffset, double yOffset) noexcept
{
    m_Fov -= static_cast<float>(yOffset);
    m_Fov = std::clamp(m_Fov, 1.0f, 150.0f);
}
