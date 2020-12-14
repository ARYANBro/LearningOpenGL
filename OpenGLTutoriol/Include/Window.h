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

    constexpr int GetWidth() const noexcept { return mWidth; }
    constexpr int GetHeight() const noexcept { return mHeight; }
    constexpr const std::string& GetName() const noexcept { return mName; }

private:
    Window(const Window&) noexcept = default;
    
    Window& operator=(const Window&) noexcept = default;

private:
    GLFWwindow* mWindowHandle;

    int mWidth;
    int mHeight;
    std::string mName;
};
