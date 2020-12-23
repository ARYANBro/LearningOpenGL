#pragma once

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
    static void BindAction(const std::string& name, const ActionCondition& condition) noexcept;
    static void BindKey(const std::string& name, int glfwKey);

private:
    static std::unordered_map<std::string, ActionCondition> s_Actions;
    static std::unordered_map<std::string, KeyCondition> s_Inputs;
};
