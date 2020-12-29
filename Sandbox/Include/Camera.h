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
    Camera(const glm::vec3& position, float speed, float senstivity) noexcept;
    Camera(const std::shared_ptr<CameraInputBindings>& inputBindings = CameraInputBindings::Create<DefaultCameraInputBindings>()) noexcept;

    void OnUpdate(DeltaTime delta) noexcept;
    void OnMouseMoved(double xPos, double yPos) noexcept;

    void SetPosition(const glm::vec3& position) noexcept { m_Position = position; }
    void SetSpeed(float newSpeed) noexcept { m_Speed = newSpeed; }
    void SetMouseSenstivity(float senstivity) noexcept { m_MouseSenstivity = senstivity; }
    void SetEulerAngles(float yaw, float pitch);
    
    const glm::mat4& GetViewMatrix() const noexcept { return m_ViewMatrix; }
    const glm::vec3& GetPosition() const noexcept { return m_Position; }
    float GetSpeed() const noexcept { return m_Speed; }
    float GetSenstivity() const noexcept{ return m_MouseSenstivity; }

    glm::vec3 GetUpDirection() const noexcept;
    glm::vec3 GetForwardDirection() const noexcept;
    glm::vec3 GetRightDirection() const noexcept;

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

    glm::vec2 m_PreviousMousePos;

private:
    void UpdateVectors() noexcept;
    void UpdatePosition(DeltaTime delta) noexcept;
    void UpdateRotation(DeltaTime delta) noexcept;
    void UpdateView() noexcept;
};
