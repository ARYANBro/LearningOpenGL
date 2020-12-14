#include "OpenGLApplication.h"

#include "Graphics/VertexBuffer.h"
#include "Graphics/ElementBuffer.h"

#include "GLFW/glfw3.h"
#include "stb_image.h"

#include <vector>
#include <iostream>

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

    const BufferLayout layout = {
        LayoutDataType::Float3,
        LayoutDataType::Float2
    };

    vertexBuffer->SetLayout(layout);

    mVao.AddVertexBuffer(vertexBuffer);

    LoadAssets();

    mPavingStonesTexture.Bind(0);

    mFabricTexture.Bind(1);

    mVao.Bind();
    mShader.Bind();

    mShader.SetInt("uPavingStonesTexture", 0);
    mShader.SetInt("uFabricTexture", 1);

    mModelMatrix = glm::mat4(1.0f);

    mViewMatrix = glm::mat4(1.0f);
    mViewMatrix = glm::translate(mViewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));
    
    mProjectionMatrix = glm::perspective(glm::radians(45.0f), static_cast<float>(GetWindow().GetHeight()) / GetWindow().GetWidth(), 0.1f, 100.0f);

    mShader.SetMat4("uProjectionMatrix", mProjectionMatrix);
    mShader.SetMat4("uViewMatrix", mViewMatrix);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void OpenGLApplication::OnUpdate() noexcept
{
    auto getKey = [this](int glfwKey)
    {
        return glfwGetKey(GetWindow().GetHandle(), glfwKey) == GLFW_PRESS;
    };

    auto rotate = [&](const glm::vec3& axis, float rotationDegrees = 5.0f)
    {
        mModelMatrix = glm::rotate(mModelMatrix, glm::radians(rotationDegrees), axis);
    };

    if (getKey(GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(GetWindow().GetHandle(), true);
    }

    if (getKey(GLFW_KEY_A))
    {
        rotate(glm::vec3(0.0f, -1.0f, 0.0f));
    }
    else if (getKey(GLFW_KEY_D))
    {
        rotate(glm::vec3(0.0f, 1.0f, 0.0f));
    }

    if (getKey(GLFW_KEY_W))
    {
        rotate(glm::vec3(-1.0f, 0.0f, 0.0f));
    }
    else if (getKey(GLFW_KEY_S))
    {
        rotate(glm::vec3(1.0f, 0.0f, 0.0f));
    }

    if (getKey(GLFW_KEY_SPACE))
    {
        mModelMatrix = glm::mat4(1.0f);
    }

    mShader.SetMat4("uModelMatrix", mModelMatrix);
}

void OpenGLApplication::OnRender() noexcept
{
    glClearColor(0.02f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glfwSwapBuffers(GetWindow().GetHandle());
    GetWindow().PollEvents();
}

void OpenGLApplication::LoadAssets() noexcept
{
    mShader.BuildFromFile("Assets/Shaders/Shader.glsl");
    mPavingStonesTexture.Load("Assets/Textures/PavingStone/PavingStones085_2K_Color.jpg");
    mFabricTexture.Load("Assets/Textures/FabricPattern/fabric_pattern_07_col_1_1k.png");    
}
