#pragma once

#include "Window.h"

#include <string>

class Application
{
public:
    Application(int windowWidth = 800, int windowHeight = 600, const std::string& windowName = "Application") noexcept;
    virtual ~Application() noexcept = default;

    void Run() noexcept;

protected:
    virtual void OnBegin() noexcept {}
    virtual void OnUpdate() noexcept;
    virtual void OnRender() noexcept {}
    virtual void OnEnd() noexcept {}

    constexpr Window& GetWindow() noexcept { return mWindow; }
    constexpr const Window& GetWindow() const noexcept { return mWindow; }

private:
    Window mWindow;
};
