#include "OpenGLApplication.h"

#include "Graphics/VertexBuffer.h"
#include "Graphics/ElementBuffer.h"

#include "GLFW/glfw3.h"
#include "stb_image.h"

#include <vector>
#include <iostream>

void OpenGLApplication::OnBegin() noexcept
{
    InitBuffers();
    LoadAssets();

    mPavingStonesTexture.Bind(0);
    mFabricTexture.Bind(1);

    mVao.Bind();
    mShader.Bind();

    mShader.SetInt("uPavingStonesTexture", 0);
    mShader.SetInt("uFabricTexture", 1);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void OpenGLApplication::OnUpdate() noexcept
{
    if (glfwGetKey(GetWindow().GetHandle(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(GetWindow().GetHandle(), true);
    }
}

void OpenGLApplication::OnRender() noexcept
{
    glClearColor(0.02f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mVao.GetElementBuffer()->GetCount()), GL_UNSIGNED_INT, nullptr);

    glfwSwapBuffers(GetWindow().GetHandle());
    GetWindow().PollEvents();
}

void OpenGLApplication::InitBuffers() noexcept
{
    const float vertcies[8 * 4] = {
        -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
         0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f
    };

    const auto vertexBuffer = std::make_shared<VertexBuffer>(vertcies, sizeof(vertcies));

    const BufferLayout layout = {
        LayoutDataType::Float3,
        LayoutDataType::Float3,
        LayoutDataType::Float2
    };

    vertexBuffer->SetLayout(layout);

    mVao.AddVertexBuffer(vertexBuffer);

    unsigned int indcies[3 * 2] = { 
        0, 1, 2,
        0, 2, 3
    };

    const auto elementBuffer = std::make_shared<ElementBuffer>(indcies, std::size(indcies));
    
    mVao.SetElementBuffer(elementBuffer);
}

void OpenGLApplication::LoadAssets() noexcept
{
    mShader.BuildFromFile("Assets/Shaders/Shader.glsl");
    
    mPavingStonesTexture.Load("Assets/Textures/PavingStone/PavingStones085_2K_Color.jpg");
    mFabricTexture.Load("Assets/Textures/FabricPattern/fabric_pattern_07_col_03_1k.png");    
}
