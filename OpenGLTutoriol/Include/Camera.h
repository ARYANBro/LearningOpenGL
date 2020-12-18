#pragma once

#include "CameraInputBindings.h"
#include "Input.h"

#include "GLFW/glfw3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <unordered_map>
#include <functional>
#include <string>
#include <memory>

class DeltaTime;

class Camera
{
public:
    const glm::vec3& Up;
    const glm::vec3& Forward;
    const glm::vec3& Right;

public:
    Camera(std::shared_ptr<CameraInputBindings> inputBindings = CameraInputBindings::Create<DefaultCameraBindings>()) noexcept;

    void Update(DeltaTime delta) noexcept;
    void OnMouseMoved(double xPos, double yPos) noexcept;

    constexpr void SetSpeed(float newSpeed) noexcept
    {
        m_Speed = newSpeed;
    }

    constexpr void SetMouseSenstivity(float senstivity) noexcept
    {
        m_MouseSenstivity = senstivity;
    }

    constexpr const glm::mat4& GetViewMatrix() const noexcept
    {
        return m_ViewMatrix;
    }

    constexpr const glm::vec3& GetPosition() noexcept
    {
        return m_Position;
    }

    constexpr float GetSenstivity() const noexcept
    {
        return m_MouseSenstivity;
    }

private:
    glm::vec3 m_Position;
    glm::mat4 m_ViewMatrix;

    float m_Speed;

    glm::vec3 m_Up;
    glm::vec3 m_Forward;
    glm::vec3 m_Right;
    glm::vec3 m_WorldUp;

    float m_MouseSenstivity;

    glm::vec3 m_EulerAngles;

    std::shared_ptr<CameraInputBindings> m_InputBindings;

private:
    void UpdateVectors() noexcept;
};
