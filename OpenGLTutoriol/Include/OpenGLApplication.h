#pragma once

#include "Application.h"

#include "Graphics/VertexArray.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"
#include "Camera.h"

#include "glm/glm.hpp"

#include <array>

class OpenGLApplication : public Application
{    
public:
    OpenGLApplication(int windowWidth, int windowHeight) noexcept
        : Application(windowWidth, windowHeight, "OpenGLApplication")
    {
    }

    virtual void OnBegin() noexcept override;
    virtual void OnUpdate(DeltaTime delta) noexcept override;
    virtual void OnRender() noexcept override;
    
    virtual void OnMouseMoved(double xPos, double yPos) noexcept override;

private:
    VertexArray m_Vao;
    
    Shader m_Shader;
    Texture m_FabricTexture;
    Texture m_PavingStonesTexture;

    glm::mat4 m_ModelMatrix = glm::mat4(1.0f);
    
    glm::mat4 m_ProjectionMatrix = glm::perspective(
        glm::radians(45.0f),
        static_cast<float>(GetWindow().GetWidth()) / GetWindow().GetHeight(),
        0.1f,
        100.0f
    );

    std::array<glm::vec3, 10> m_CubePositions = {
        glm::vec3( 0.0f,  0.0f,  0.0f ),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f ),
        glm::vec3(-3.8,  -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f ),
        glm::vec3(-1.7f,  3.0f, -7.5f ),
        glm::vec3( 1.3f, -2.0f, -2.5f ),
        glm::vec3( 1.5f,  2.0f, -2.5f ),
        glm::vec3( 1.5f,  0.2f, -1.5f ),
        glm::vec3(-1.3f,  1.0f, -1.5f )
    };

    float m_Fov = 45.0f;

    Camera m_Camera;
};
