#include "Camera.h"

#include "DeltaTime.h"
#include "Input.h"
#include "Application.h"

#include <glm/gtc/matrix_transform.hpp>

#include <cassert>

static glm::mat4 LookAt(const glm::vec3& position, const glm::vec3& target, const glm::vec3& worldUp) noexcept
{
    const glm::vec3 forward = glm::normalize(position - target);
    const glm::vec3 right = glm::normalize(glm::cross(worldUp, forward));
    const glm::vec3 up = glm::cross(forward, right);

    glm::mat4 translation(1.0f);
    glm::mat4 rotation(1.0f);

    translation[3][0] = -position.x;
    translation[3][1] = -position.y;
    translation[3][2] = -position.z;

    rotation[0][0] = right.x;
    rotation[1][0] = right.y;
    rotation[2][0] = right.z;

    rotation[0][1] = up.x;
    rotation[1][1] = up.y;
    rotation[2][1] = up.z;

    rotation[0][2] = forward.x;
    rotation[1][2] = forward.y;
    rotation[2][2] = forward.z;

    return rotation * translation;
}

Camera::Camera(const glm::vec3& position, float speed, float senstivity) noexcept
    : m_Position(position), m_ViewMatrix(1.0f), m_Speed(speed), m_Up(), m_Forward(0.0f, 0.0f, -1.0f), m_Right(), 
    m_WorldUp(0.0f, 1.0f, 0.0f), m_MouseSenstivity(senstivity), m_EulerAngles(270.0f, 0.0f, 0.0f), m_InputBindings(CameraInputBindings::Create<DefaultCameraInputBindings>()),
    m_PreviousMousePos(Input::GetMousePosition())
{
}

Camera::Camera(const std::shared_ptr<CameraInputBindings>& inputBindings) noexcept
    : Camera({}, 2.0f, 8.0f)
{
    m_InputBindings = inputBindings;
    UpdateView();
}

void Camera::Update(DeltaTime delta) noexcept
{
    UpdatePosition(delta);
    UpdateRotation(delta);
    UpdateView();
}

void Camera::SetEulerAngles(float yaw, float pitch)
{
    m_EulerAngles = glm::vec3(yaw, pitch, 0.0f);
    UpdateView();
}

glm::vec3 Camera::GetUpDirection() const noexcept
{
    return glm::normalize(glm::cross(m_Right, m_Forward));
}

glm::vec3 Camera::GetForwardDirection() const noexcept
{
    return glm::normalize(glm::vec3(
        std::cos(glm::radians(m_EulerAngles.x)) * std::cos(glm::radians(m_EulerAngles.y)),
        std::sin(glm::radians(m_EulerAngles.y)),
        std::sin(glm::radians(m_EulerAngles.x)) * std::cos(glm::radians(m_EulerAngles.y))
    ));
}

glm::vec3 Camera::GetRightDirection() const noexcept
{
    return glm::normalize(glm::cross(m_Forward, m_WorldUp));
}

void Camera::UpdateView() noexcept
{
    m_Forward = GetForwardDirection();
    m_Right = GetRightDirection();
    m_Up = GetUpDirection();

    m_ViewMatrix = LookAt(m_Position, m_Position + m_Forward, m_WorldUp);
}

void Camera::UpdateRotation(DeltaTime delta) noexcept
{
    glm::vec2 mouse = Input::GetMousePosition();
    glm::vec2 offset = (mouse - m_PreviousMousePos) * delta.operator float();
    m_PreviousMousePos = mouse;

    if ((Input::IsKeyPressed(GLFW_KEY_LEFT_ALT) && Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_MIDDLE)) ||
        Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
    {
        m_EulerAngles += glm::vec3(offset.x, -offset.y, 0.0f) * m_MouseSenstivity;
        m_EulerAngles.y = std::clamp(m_EulerAngles.y, -89.0f, 89.0f);    
    }
}

void Camera::UpdatePosition(DeltaTime delta) noexcept
{
    if (Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
    {
        if (m_InputBindings->MoveForward())
        {
            m_Position += m_Speed * delta * m_Forward;
        }
        else if (m_InputBindings->MoveBackward())
        {
            m_Position -= m_Speed * delta * m_Forward;
        }

        if (m_InputBindings->MoveLeft())
        {
            m_Position -= m_Speed * delta * m_Right;
        }
        else if (m_InputBindings->MoveRight())
        {
            m_Position += m_Speed * delta * m_Right;
        }

        if (m_InputBindings->MoveUp())
        {
            m_Position += m_Speed * delta * m_Up;
        }
        else if (m_InputBindings->MoveDown())
        {
            m_Position -= m_Speed * delta * m_Up;
        }
    }
}
