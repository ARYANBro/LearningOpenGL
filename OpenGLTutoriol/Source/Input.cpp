#include "Input.h"

#include "Application.h"

#include "GLFW/glfw3.h"

#include <cassert>

std::unordered_map<std::string, Input::ActionCondition> Input::s_Actions;
std::unordered_map<std::string, Input::KeyCondition> Input::s_Inputs;

bool Input::IsActionTriggered(const std::string& name) noexcept
{
    if (!s_Actions.contains(name))
    {
        return false;
    }

    return s_Actions[name]();
}

bool Input::IsKeyPressed(const std::string& name) noexcept  
{
    if (!s_Inputs.contains(name))
    {
        return false;
    }

    return s_Inputs[name]() == GLFW_PRESS;
}

bool Input::IsKeyPressed(int glfwKey) noexcept
{
    return glfwGetKey(Application::Get()->GetWindow().GetHandle(), glfwKey) == GLFW_PRESS;
}

void Input::BindAction(const std::string& name, const ActionCondition& condition) noexcept
{
    s_Actions[name] = condition;
}

void Input::BindKey(const std::string& name, int glfwKey)
{
    s_Inputs[name] = [glfwKey]()
    {
        return glfwGetKey(Application::Get()->GetWindow().GetHandle(), glfwKey);
    };
}
