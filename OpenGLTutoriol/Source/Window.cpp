#include "Window.h"

#include "GLFW/glfw3.h"

#include <cassert>

Window::Window(int width, int height, const std::string& name) noexcept
    : mWindowHandle(nullptr),
    mWidth(width), mHeight(height),
    mName(name)
{
    const int glfwInitResult = glfwInit();
    assert(glfwInitResult);

    mWindowHandle = glfwCreateWindow(mWidth, mHeight, mName.c_str(), nullptr, nullptr);
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
