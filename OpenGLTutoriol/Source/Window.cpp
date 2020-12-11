#include "Window.h"

Window::Window(int width, int height, const std::string& name) noexcept
    : mWindowHandle(nullptr)
{
    assert(glfwInit());

    mWindowHandle = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
    assert(mWindowHandle);
}

Window::~Window() noexcept
{
    glfwTerminate();
}

bool Window::IsClosed() const noexcept
{
    return glfwWindowShouldClose(mWindowHandle);
}

void Window::PollEvents() const noexcept
{
    glfwPollEvents();
}
