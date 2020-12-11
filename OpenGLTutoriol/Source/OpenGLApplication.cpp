#include "OpenGLApplication.h"

#include "Graphics/VertexBuffer.h"
#include "Graphics/ElementBuffer.h"
#include "Graphics/VertexArray.h"

#include "Graphics/Shader.h"

#include <vector>
#include <iostream>

void OpenGLApplication::OnBegin() noexcept
{
    const float vertcies[6 * 4] = {
        -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f
    };

    const auto vertexBuffer = std::make_shared<VertexBuffer>(vertcies, sizeof(vertcies));

    const BufferLayout layout = {
        LayoutDataType::Float3,
        LayoutDataType::Float3
    };

    vertexBuffer->SetLayout(layout);

    mVao.AddVertexBuffer(vertexBuffer);

    unsigned int indcies[3 * 2] = { 
        0, 1, 2,
        0, 2, 3
    };

    const auto elementBuffer = std::make_shared<ElementBuffer>(indcies, std::size(indcies));
    
    mVao.SetElementBuffer(elementBuffer);

    constexpr const char* vertexShader = R"(
        #version 460 core

        layout (location = 0) in vec3 aPosition;
        layout (location = 1) in vec3 aColor;

        out vec4 vColor;

        void main()
        {
            vColor = vec4(aColor, 1.0f);
            gl_Position = vec4(aPosition, 1.0f);
        }
    )";

    constexpr const char* fragmentShader = R"(
        #version 460 core

        out vec4 FragColor;

        in vec4 vColor;

        void main()
        {
            FragColor = vColor;
        }
    )";

    try
    {
        mShader.BuildShaders(vertexShader, fragmentShader);
    }
    catch (const std::exception& except)
    {
        std::cerr << "An exception has occured: " << except.what() << std::endl;
        std::cin.get();
    }

    mShader.Bind();
    mVao.Bind();
}

void OpenGLApplication::OnUpdate() noexcept
{
}

void OpenGLApplication::OnRender() noexcept
{
    glClearColor(0.02f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mVao.GetElementBuffer()->GetCount()), GL_UNSIGNED_INT, nullptr);

    glfwSwapBuffers(GetWindow().GetHandle());
    GetWindow().PollEvents();
}
