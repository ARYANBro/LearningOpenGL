#pragma once

class GLFWwindow;

#include <functional>
#include <string>

class Window
{
public:
    using MouseMovedCallbackFunction = std::function<void(double, double)>;
    using MouseScrolledCallbackFunction = std::function<void(double, double)>;

public:
    Window(std::uint_fast32_t width = 800, std::uint_fast32_t height = 600, const std::string& name = "Window") noexcept;
    ~Window();

    bool IsClosed() const noexcept;
    void PollEvents() const noexcept;

    void SetMouseMovedCallback(const MouseMovedCallbackFunction& mouseMovedCallback) noexcept;
    void SetMouseScrolledCallback(const MouseScrolledCallbackFunction& mouseScrolledCallbac) noexcept;

    const GLFWwindow* GetHandle() const noexcept { return m_WindowHandle; }
    GLFWwindow* GetHandle() noexcept { return m_WindowHandle; }
    std::uint_fast32_t GetWidth() const noexcept { return m_Width; }
    std::uint_fast32_t GetHeight() const noexcept { return m_Height; }
    const std::string& GetName() const noexcept { return m_Name; }

private:
    struct WindowData
    {
        MouseMovedCallbackFunction MouseMovedCallback;
        MouseScrolledCallbackFunction MouseScrolledCallback;
    };

private:
    GLFWwindow* m_WindowHandle;

    std::uint_fast32_t m_Width;
    std::uint_fast32_t m_Height;
    std::string m_Name;

    WindowData m_Data;

private:
    Window(const Window&) noexcept = default;
    
    Window& operator=(const Window&) noexcept = default;
};
