#include "Window.h"

#include <GLFW/glfw3.h>

#include <cassert>

Window::Window(std::uint_fast32_t width, std::uint_fast32_t height, const std::string& name) noexcept
    : m_WindowHandle(nullptr), m_Width(width), m_Height(height), m_Name(name)
{
    const int glfwInitResult = glfwInit();
    assert(glfwInitResult);

    m_WindowHandle = glfwCreateWindow(static_cast<int>(m_Width), static_cast<int>(m_Height), m_Name.c_str(), nullptr, nullptr);
    assert(m_WindowHandle);

    glfwSetWindowUserPointer(m_WindowHandle, &m_Data);
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

void Window::SwapBuffers() const noexcept
{
    glfwSwapBuffers(m_WindowHandle);
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

void Window::SetKeyCallback(const KeyCallbackFunction& keyCallback) noexcept
{
    m_Data.KeyCallback = keyCallback;
    
    glfwSetKeyCallback(m_WindowHandle, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        data->KeyCallback(key, action);
    });
}
