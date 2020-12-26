#pragma once

#include "Application.h"

#include "Graphics/Shader.h"
#include "Graphics/Meshes/Cube.h"
#include "Camera.h"


#include "glm/glm.hpp"

#include <array>

class Sandbox : public Application
{    
public:
    Sandbox(std::uint_fast32_t windowWidth, std::uint_fast32_t windowHeight) noexcept
        : Application(windowWidth, windowHeight, "Sandbox")
    {
    }

    virtual void OnBegin() noexcept override;
    virtual void OnUpdate(DeltaTime delta) noexcept override;
    virtual void OnRender() noexcept override;
    virtual void OnImGuiRender() noexcept override;

private:
    Cube m_Cube;
    glm::vec3 m_CubePosition;
    float m_SpecularStrength = 0.1f;
    int m_Shininess = 32;
    float m_AmbientStrength = 0.1;

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

    Camera m_Camera{{ -0.5f, 1.5f, 5.0f }, 2.0f, 8.0f };

    bool m_SpecularChecked = true;
    bool m_AmbientChecked = true;
    bool m_DiffuseChecked = true;

    float m_FrameTime;
};
