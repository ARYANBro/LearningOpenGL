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
    Window(int width = 800, int height = 600, const std::string& name = "Window") noexcept;
    ~Window();

    bool IsClosed() const noexcept;
    void PollEvents() const noexcept;

    void SetMouseMovedCallback(const MouseMovedCallbackFunction& mouseMovedCallback) noexcept;
    void SetMouseScrolledCallback(const MouseScrolledCallbackFunction& mouseScrolledCallbac) noexcept;

    constexpr const GLFWwindow* GetHandle() const noexcept
    {
        return m_WindowHandle;
    }

    constexpr GLFWwindow* GetHandle() noexcept
    {
        return m_WindowHandle;
    }

    constexpr int GetWidth() const noexcept
    {
        return m_Width;
    }

    constexpr int GetHeight() const noexcept
    {
        return m_Height;
    }

    constexpr const std::string& GetName() const noexcept
    {
        return m_Name;
    }

private:
    struct WindowData
    {
        MouseMovedCallbackFunction MouseMovedCallback;
        MouseScrolledCallbackFunction MouseScrolledCallback;
    };
    
private:
    GLFWwindow* m_WindowHandle;

    int m_Width;
    int m_Height;
    std::string m_Name;

    WindowData m_Data;

private:
    Window(const Window&) noexcept = default;
    
    Window& operator=(const Window&) noexcept = default;
};
