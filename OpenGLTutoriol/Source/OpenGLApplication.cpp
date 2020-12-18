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

std::ostream& operator<<(std::ostream& out, const glm::vec3& vec)
{
    out << "vec3(" << vec.x << ", " << vec.y << ", " << vec.z << ')';
    return out;
}

void OpenGLApplication::OnBegin() noexcept
{
    const float vertcies[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    const auto vertexBuffer = std::make_shared<VertexBuffer>(vertcies, sizeof(vertcies));

    vertexBuffer->SetLayout({
        LayoutDataType::Float3,
        LayoutDataType::Float2
    });

    m_Vao.AddVertexBuffer(vertexBuffer);

    m_Shader.BuildFromFile("Assets/Shaders/Shader.glsl");
    m_PavingStonesTexture.Load("Assets/Textures/PavingStone/PavingStones085_2K_Color.jpg");
    m_FabricTexture.Load("Assets/Textures/FabricPattern/fabric_pattern_07_col_1_1k.png");    

    m_PavingStonesTexture.Bind(0);
    m_FabricTexture.Bind(1);

    m_Vao.Bind();
    m_Shader.Bind();

    m_Shader.SetInt("u_PavingStonesTexture", 0);
    m_Shader.SetInt("u_FabricTexture", 1);
    m_Shader.SetMat4("u_ProjectionMatrix", m_ProjectionMatrix);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    Input::BindKey("Quit", GLFW_KEY_ESCAPE);
}

void OpenGLApplication::OnUpdate(DeltaTime delta) noexcept
{
    if (Input::IsKeyPressed("Quit"))
    {
        glfwSetWindowShouldClose(GetWindow().GetHandle(), true);
    }

    m_Camera.Update(delta);

    std::cerr << m_Camera.GetViewMatrix()[2] << std::endl;

    m_Shader.Bind();
    m_Shader.SetMat4("u_ViewMatrix", m_Camera.GetViewMatrix());
}

void OpenGLApplication::OnRender() noexcept
{
    glClearColor(0.02f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (std::size_t i = 0; i < m_CubePositions.size(); i++)
    {
        m_ModelMatrix = glm::mat4(1.0f);
        m_ModelMatrix = glm::translate(m_ModelMatrix, m_CubePositions[i]);
        
        std::srand(i * i);

        if (i % 5 == 0)
        {
            glm::vec3 randomRotation(std::rand(), std::rand(), std::rand());
          
            m_ModelMatrix = glm::rotate(m_ModelMatrix, 360.0f * (std::rand() * 1.0f / RAND_MAX), randomRotation);
        }

        m_Shader.Bind();
        m_Shader.SetMat4("u_ModelMatrix", m_ModelMatrix);
        
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    glfwSwapBuffers(GetWindow().GetHandle());
    GetWindow().PollEvents();
}

void OpenGLApplication::OnMouseMoved(double xPos, double yPos) noexcept
{
    m_Camera.OnMouseMoved(xPos, yPos);
}
