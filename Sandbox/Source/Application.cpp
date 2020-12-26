#include "Application.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

#include <chrono>
#include <iostream>
#include <cassert>

Application* Application::s_Application = nullptr;

Application::Application() noexcept
    : m_Window() 
{
    Init();
}

Application::Application(std::uint_fast32_t windowWidth, std::uint_fast32_t windowHeight, const std::string& windowName) noexcept
    : m_Window(windowWidth, windowHeight, windowName)
{
    Init();
}

Application::~Application() noexcept
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Application::Run() noexcept
{
    OnBegin();

    DeltaTime delta;
    
    while (!m_Window.IsClosed())
    {
        delta.Calculate();

        OnUpdate(delta);

        OnBeginFrame();
        OnRender();
        ImGuiRender();
        OnEndFrame();
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
            default: break;
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

    m_Window.SetKeyCallback([this](int key, int action)
    {
        OnKeyPressed(key, action);
    });

    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(GetWindow().GetHandle(), true);
    ImGui_ImplOpenGL3_Init("#version 460 core");
}

void Application::OnBeginFrame() const noexcept
{
    glClearColor(0.02f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Application::OnEndFrame() const noexcept
{
    m_Window.SwapBuffers();
    m_Window.PollEvents();
}

void Application::ImGuiRender() noexcept
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    OnImGuiRender();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
