#include "Camera.h"

#include "DeltaTime.h"
#include "Input.h"

#include "glm/gtc/matrix_transform.hpp"

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

Camera::Camera(std::shared_ptr<CameraInputBindings> inputBindings) noexcept
    : Up(m_Up), Forward(m_Forward), Right(m_Right), m_Position(), m_ViewMatrix(1.0f), m_Speed(2.5f), m_Up(), m_Forward(0.0f, 0.0f, -1.0f), m_Right(), 
      m_WorldUp(0.0f, 1.0f, 0.0f), m_MouseSenstivity(0.3f), m_EulerAngles(270.0f, 0.0f, 0.0f), m_InputBindings(inputBindings)
{
    UpdateVectors();
}

void Camera::Update(DeltaTime delta) noexcept
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

    m_ViewMatrix = LookAt(m_Position, m_Position + m_Forward, m_WorldUp);
}

void Camera::OnMouseMoved(double xPos, double yPos) noexcept
{
    static glm::vec2 s_PreviousMousePos(xPos, yPos); 
    const glm::vec2 offset(xPos - s_PreviousMousePos.x, s_PreviousMousePos.y - yPos);
  
    m_EulerAngles += glm::vec3(offset, 0.0f) * m_MouseSenstivity;
    s_PreviousMousePos = glm::vec2(xPos, yPos);
    m_EulerAngles.y = std::clamp(m_EulerAngles.y, -89.0f, 89.0f);    

    UpdateVectors();
}

void Camera::UpdateVectors() noexcept
{
    m_Forward = glm::vec3(
        std::cos(glm::radians(m_EulerAngles.x)) * std::cos(glm::radians(m_EulerAngles.y)),
        std::sin(glm::radians(m_EulerAngles.y)),
        std::sin(glm::radians(m_EulerAngles.x)) * std::cos(glm::radians(m_EulerAngles.y))
    );

    m_Forward = glm::normalize(m_Forward);
    m_Right = glm::normalize(glm::cross(m_Forward, m_WorldUp));
    m_Up = glm::normalize(glm::cross(m_Right, m_Forward));
}
