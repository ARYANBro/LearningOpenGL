#pragma once

#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include <string>
#include <cassert>

class Window
{
public:
    Window(int width = 800, int height = 600, const std::string& name = "Window") noexcept;
    Window(const Window&) noexcept = delete;
    ~Window();

    bool IsClosed() const noexcept;
    void PollEvents() const noexcept;

    constexpr const GLFWwindow* GetHandle() const noexcept { return mWindowHandle; }
    constexpr GLFWwindow* GetHandle() noexcept { return mWindowHandle; }

public:
    Window& operator=(const Window&) noexcept = delete;

private:
    GLFWwindow* mWindowHandle;
};
