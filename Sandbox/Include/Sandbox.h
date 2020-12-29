#pragma once

#include "Application.h"

#include "Graphics/Shader.h"
#include "Graphics/Meshes/CubeMesh.h"
#include "Camera.h"
#include "CubeObject.h"
#include "LightObject.h"

#include <glm/glm.hpp>
#include <imgui.h>

#include <array>
#include <iostream>

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
    CubeObject m_Emerald;
    CubeObject m_Jade{ m_Emerald.GetMesh() };
    LightObject m_Light{ m_Emerald.GetMesh() };

    float m_FrameTime;

    glm::mat4 m_ModelMatrix{ 1.0f };
    Camera m_Camera{{ -0.5f, 1.5f, 5.0f }, 2.0f, 0.5f};

    glm::mat4 m_ProjectionMatrix;
    float m_Fov = 45.0f;
    const float m_AspectRatio = static_cast<float>(GetWindow().GetWidth()) / GetWindow().GetHeight();
    const float m_ZNear = 0.1f, m_ZFar = 1000.0f;

private:
    void AddObjectProperties(const std::string& name, Object& object) noexcept;
};
