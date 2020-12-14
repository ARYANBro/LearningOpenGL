#include "Application.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include <iostream>
#include <cassert>

Application::Application() noexcept
    : mWindow() 
{
    InitRenderingContext();
}

Application::Application(int windowWidth, int windowHeight, const std::string& windowName) noexcept
    : mWindow(windowWidth, windowHeight, windowName)
{
    InitRenderingContext();
}

void Application::Run() noexcept
{
    OnBegin();

    while (!mWindow.IsClosed())
    {
        OnUpdate();
        OnRender();
    }

    OnEnd();
}

void Application::InitRenderingContext() noexcept
{
    GLFWwindow* windowHandle = mWindow.GetHandle();

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
}
