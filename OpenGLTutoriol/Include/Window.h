#pragma once

class GLFWwindow;

#include <string>

class Window
{
public:
    Window(int width = 800, int height = 600, const std::string& name = "Window") noexcept;
    ~Window();

    bool IsClosed() const noexcept;
    void PollEvents() const noexcept;

    constexpr const GLFWwindow* GetHandle() const noexcept { return mWindowHandle; }
    constexpr GLFWwindow* GetHandle() noexcept { return mWindowHandle; }

private:
    GLFWwindow* mWindowHandle;
};
