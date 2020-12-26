#pragma once

#include <glm/glm.hpp>

#include <functional>
#include <string>
#include <unordered_map>

class Input
{
public:
    using ActionCondition = std::function<bool()>;
    using KeyCondition = std::function<int()>;

public:
    static bool IsActionTriggered(const std::string& name) noexcept;
    static bool IsKeyPressed(const std::string& name) noexcept;
    static bool IsKeyPressed(int glfwKey) noexcept;
    static bool IsMouseButtonPressed(int glfwMoseButton) noexcept;
    static void BindAction(const std::string& name, const ActionCondition& condition) noexcept;
    static void BindKey(const std::string& name, int glfwKey);

    static glm::vec2 GetMousePosition() noexcept;
    static float GetMouseX() noexcept;
    static float GetMouseY() noexcept;

private:
    static std::unordered_map<std::string, ActionCondition> s_Actions;
    static std::unordered_map<std::string, KeyCondition> s_Inputs;
};
