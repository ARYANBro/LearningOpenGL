#pragma once

#include "Application.h"

#include "Graphics/Shader.h"
#include "Graphics/Meshes/Cube.h"

#include "Camera.h"

#include "glm/glm.hpp"

#include <array>


class OpenGLApplication : public Application
{    
public:
    OpenGLApplication(std::uint_fast32_t windowWidth, std::uint_fast32_t windowHeight) noexcept
        : Application(windowWidth, windowHeight, "OpenGLApplication")
    {
    }

    virtual void OnBegin() noexcept override;
    virtual void OnUpdate(DeltaTime delta) noexcept override;
    virtual void OnRender() noexcept override;

    virtual void OnMouseMoved(double xPos, double yPos) noexcept override;
    virtual void OnMouseScrolled(double xOffset, double yOffset) noexcept override;

private:
    Cube m_Cube;
    Cube m_Light = Mesh::Share(m_Cube);

    glm::vec3 m_LightPosition;
    glm::vec3 m_LightColor;

    std::shared_ptr<Shader> m_CubeShader;
    std::shared_ptr<Shader> m_LightShader;

    glm::mat4 m_ModelMatrix = glm::mat4(1.0f);

    glm::mat4 m_ProjectionMatrix = glm::perspective(glm::radians(m_Fov), m_AspectRatio, m_ZNear, m_ZFar);
    float m_Fov = 45.0f;
    const float m_AspectRatio = static_cast<float>(GetWindow().GetWidth()) / GetWindow().GetHeight();
    const float m_ZNear = 0.1f;
    const float m_ZFar = 100.0f;

    Camera m_Camera;
};
