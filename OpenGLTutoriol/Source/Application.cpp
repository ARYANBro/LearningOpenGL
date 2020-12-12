#include "Application.h"

#include <iostream>

static void InitRenderingContext(Window& window) noexcept
{
    GLFWwindow* windowHandle = window.GetHandle();

    glfwMakeContextCurrent(windowHandle);

    glfwWindowHint(GLFW_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    const int gladInitResult = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

    assert(gladInitResult);

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    auto openGLMessageCallback = [](GLenum, GLenum, GLuint, GLenum severity, GLsizei, const GLchar* message, const void*)
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

    glDebugMessageCallback(openGLMessageCallback, nullptr);
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

    glfwSetFramebufferSizeCallback(windowHandle, [](GLFWwindow*, int width, int height)
    {
        glViewport(0, 0, width, height);
    });
}

Application::Application(int windowWidth, int windowHeight, const std::string& windowName) noexcept
    : mWindow(windowWidth, windowHeight, windowName)
{
    InitRenderingContext(mWindow);
}

void Application::Run() noexcept
{
    OnBegin();

    while (!mWindow.IsClosed())
    {
        Application::OnUpdate();
        OnUpdate();

        Application::OnRender();
        OnRender();
    }

    OnEnd();
}

void Application::OnUpdate() noexcept
{
    GLFWwindow* windowHandle = mWindow.GetHandle();

    if (glfwGetKey(windowHandle, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(windowHandle, true);
    }

    mWindow.PollEvents();
}
