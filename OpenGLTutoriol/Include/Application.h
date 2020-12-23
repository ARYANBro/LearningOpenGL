#pragma once

#include "Window.h"
#include "DeltaTime.h"

#include <string>

class Application
{
public:
    Application() noexcept;
    Application(std::uint_fast32_t windowWidth, std::uint_fast32_t windowHeight, const std::string& windowName) noexcept;
    virtual ~Application() noexcept = default;

    void Run() noexcept;

    virtual void OnBegin() noexcept {}
    virtual void OnUpdate([[maybe_unused]] DeltaTime delta) noexcept {}
    virtual void OnRender() noexcept {}
    virtual void OnEnd() noexcept {}
    virtual void OnMouseMoved([[maybe_unused]] double xPos, [[maybe_unused]] double yPos) noexcept {}
    virtual void OnMouseScrolled([[maybe_unused]] double xOffset, [[maybe_unused]] double yOffset) noexcept {}

    static Application* Get() noexcept { return s_Application; }
    Window& GetWindow() noexcept { return m_Window; }
    const Window& GetWindow() const noexcept { return m_Window; }

private:
    Window m_Window;

    static Application* s_Application;

private:
    void Init() noexcept;
};
