#include "Application.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include <chrono>
#include <iostream>
#include <cassert>

Application* Application::s_Application = nullptr;

Application::Application() noexcept
    : m_Window() 
{
    Init();
}

Application::Application(int windowWidth, int windowHeight, const std::string& windowName) noexcept
    : m_Window(windowWidth, windowHeight, windowName)
{
    Init();
}

void Application::Run() noexcept
{
    OnBegin();

    DeltaTime delta;
    
    while (!m_Window.IsClosed())
    {
        delta.Calculate();

        OnUpdate(delta);
        OnRender();
    }

    OnEnd();
}

void Application::Init() noexcept
{
    s_Application = this;
    GLFWwindow* windowHandle = m_Window.GetHandle();

    glfwMakeContextCurrent(windowHandle);

    glfwWindowHint(GLFW_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    const int gladInitResult = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
    assert(gladInitResult);

    auto debugMessageCallback = [](GLenum, GLenum, GLuint, GLenum severity, GLsizei, const GLchar* message, const void*)
    {
        switch (severity)
        {
        case GL_DEBUG_SEVERITY_HIGH:
            std::cerr << "OpenGL Severity High: " << message << std::endl;
            break;

        case GL_DEBUG_SEVERITY_MEDIUM:
            std::cerr << "OpenGL Severity Medium: " << message << std::endl;
            break;

        case GL_DEBUG_SEVERITY_LOW:
            std::cerr << "OpenGL Severity Low: " << message << std::endl;
            break;

        case GL_DEBUG_SEVERITY_NOTIFICATION:
        default:
            break;
        }
    };

    glDebugMessageCallback(debugMessageCallback, nullptr);
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

    glfwSetFramebufferSizeCallback(windowHandle, [](GLFWwindow*, int width, int height)
    {
        glViewport(0, 0, width, height);
    });

    m_Window.SetMouseMovedCallback([this](double xPos, double yPos)
    {
        OnMouseMoved(xPos, yPos);
    });

    m_Window.SetMouseScrolledCallback([this](double xOffset, double yOffset)
    {
        OnMouseScrolled(xOffset, yOffset);
    });
}
