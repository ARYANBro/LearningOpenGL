#include "Sandbox.h"

#include "Graphics/VertexBuffer.h"
#include "Graphics/ElementBuffer.h"

#include "DeltaTime.h"
#include "Input.h"

#include "GLFW/glfw3.h"
#include "stb_image.h"

#include <vector>
#include <cassert>
#include <iostream>

void Sandbox::OnBegin() noexcept
{
    Input::BindAction("MiddleMouseButtonPressed", [this]()
    {
        return glfwGetMouseButton(GetWindow().GetHandle(), GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS;
    });

    m_Camera.SetPosition(glm::vec3(-0.5f, 1.0f, 4.0f));
    m_Camera.SetEulerAngles(280.0f, -10.0f);

    try
    {
        m_CubeShader = Shader::Create("Assets/Shaders/Cube.glsl");
        m_Cube.SetShader(m_CubeShader);

        m_LightShader = Shader::Create("Assets/Shaders/Light.glsl");
        m_Light.SetShader(m_LightShader);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    m_LightColor = glm::vec3((std::cos(glfwGetTime()) + 1.5) / 2);
    m_LightPosition = glm::vec3(1.2f, 1.0f, 2.0f);
    m_CubePosition = glm::vec3(0.0f, 0.0f, 0.0f);

    m_CubeShader->Bind();
    m_CubeShader->SetInt("u_Shininess", 2);
    m_CubeShader->SetFloat("u_SpecularStrength", 0.5f);

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

    if (Input::IsActionTriggered("MiddleMouseButtonPressed"))
    {
        m_Fov = 45.0f;
    }

    m_CubeShader->Bind();
    if (Input::IsKeyPressed(GLFW_KEY_0) && !Input::IsKeyPressed(GLFW_KEY_LEFT_CONTROL))        // 0 is normal shading
    {
        m_CubeShader->SetInt("u_Mode", 0);
    }
    else if (Input::IsKeyPressed(GLFW_KEY_1) && !Input::IsKeyPressed(GLFW_KEY_LEFT_CONTROL))   // 1 is diffuse shading
    {
        m_CubeShader->SetInt("u_Mode", 1);
    }
    else if (Input::IsKeyPressed(GLFW_KEY_2) && !Input::IsKeyPressed(GLFW_KEY_LEFT_CONTROL))   // 2 is ambient color
    {
        m_CubeShader->SetInt("u_Mode", 2);
    }
    else if (Input::IsKeyPressed(GLFW_KEY_3) && !Input::IsKeyPressed(GLFW_KEY_LEFT_CONTROL))   // 3 is specular
    {
        m_CubeShader->SetInt("u_Mode", 3);
    }
    else if (Input::IsKeyPressed(GLFW_KEY_4) && !Input::IsKeyPressed(GLFW_KEY_LEFT_CONTROL))   // 4 are normals
    {
        m_CubeShader->SetInt("u_Mode", 4);
    }


    if (Input::IsKeyPressed(GLFW_KEY_0) && Input::IsKeyPressed(GLFW_KEY_LEFT_CONTROL))        
    {
        m_CubeShader->SetInt("u_Shininess", 2);
    }
    else if (Input::IsKeyPressed(GLFW_KEY_1) && Input::IsKeyPressed(GLFW_KEY_LEFT_CONTROL))  
    {
        m_CubeShader->SetInt("u_Shininess", 4);
    }
    else if (Input::IsKeyPressed(GLFW_KEY_2) && Input::IsKeyPressed(GLFW_KEY_LEFT_CONTROL))   
    {
        m_CubeShader->SetInt("u_Shininess", 8);
    }
    else if (Input::IsKeyPressed(GLFW_KEY_3) && Input::IsKeyPressed(GLFW_KEY_LEFT_CONTROL))
    {
        m_CubeShader->SetInt("u_Shininess", 16);
    }
    else if (Input::IsKeyPressed(GLFW_KEY_4) && Input::IsKeyPressed(GLFW_KEY_LEFT_CONTROL))
    {
        m_CubeShader->SetInt("u_Shininess", 32);
    }
    else if (Input::IsKeyPressed(GLFW_KEY_5) && Input::IsKeyPressed(GLFW_KEY_LEFT_CONTROL))  
    {
        m_CubeShader->SetInt("u_Shininess", 64);
    }
    else if (Input::IsKeyPressed(GLFW_KEY_6) && Input::IsKeyPressed(GLFW_KEY_LEFT_CONTROL))
    {
        m_CubeShader->SetInt("u_Shininess", 128);
    }
    else if (Input::IsKeyPressed(GLFW_KEY_7) && Input::IsKeyPressed(GLFW_KEY_LEFT_CONTROL))
    {
        m_CubeShader->SetInt("u_Shininess", 256);
    }


    m_ProjectionMatrix = glm::perspective(glm::radians(m_Fov), m_AspectRatio, m_ZNear, m_ZFar);
    m_Camera.Update(delta);
}

void Sandbox::OnRender() noexcept
{
    glClearColor(0.02f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

    m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(m_LightPosition));
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
    glfwSwapBuffers(GetWindow().GetHandle());
    GetWindow().PollEvents();
}

void Sandbox::OnMouseMoved(double xPos, double yPos) noexcept
{
    m_Camera.OnMouseMoved(xPos, yPos);
}

void Sandbox::OnMouseScrolled([[maybe_unused]] double xOffset, double yOffset) noexcept
{
    m_Fov -= static_cast<float>(yOffset);
    m_Fov = std::clamp(m_Fov, 1.0f, 150.0f);
}
