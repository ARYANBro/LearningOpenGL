#include "Window.h"

#include "GLFW/glfw3.h"

#include <cassert>

Window::Window(int width, int height, const std::string& name) noexcept
    : m_WindowHandle(nullptr), m_Width(width), m_Height(height), m_Name(name)
{
    const int glfwInitResult = glfwInit();
    assert(glfwInitResult);

    m_WindowHandle = glfwCreateWindow(m_Width, m_Height, m_Name.c_str(), nullptr, nullptr);
    assert(m_WindowHandle);

    glfwSetWindowUserPointer(m_WindowHandle, &m_Data);
    glfwSetInputMode(m_WindowHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Window::~Window() noexcept
{
    glfwTerminate();
}

bool Window::IsClosed() const noexcept
{
    return glfwWindowShouldClose(m_WindowHandle);
}

void Window::PollEvents() const noexcept
{
    glfwPollEvents();
}

void Window::SetMouseMovedCallback(const MouseMovedCallbackFunction& mouseMovedFunction) noexcept
{   
    m_Data.MouseMovedCallback = mouseMovedFunction;

    glfwSetCursorPosCallback(m_WindowHandle, [](GLFWwindow* window, double xPos, double yPos)
    {
        WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        data->MouseMovedCallback(xPos, yPos);
    });
}

void Window::SetMouseScrolledCallback(const MouseScrolledCallbackFunction& mouseScrolledCallback) noexcept
{
    m_Data.MouseScrolledCallback = mouseScrolledCallback;

    glfwSetScrollCallback(m_WindowHandle, [](GLFWwindow* window, double xOffset, double yOffset)
    {
        WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        data->MouseScrolledCallback(xOffset, yOffset);
    });
}
