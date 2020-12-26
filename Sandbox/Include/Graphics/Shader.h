#pragma once

#include "glm/gtc/matrix_transform.hpp"
#include "glad/glad.h"

#include <string>
#include <memory>
#include <unordered_map>

class Shader
{
public:
    Shader() noexcept
         : m_RendererID(0)  {}
         
    Shader(const std::string& vertexSource, const std::string& fragmentSource);
    Shader(const std::string& filePath);
    ~Shader() noexcept;

    template<typename... StringArgs>
    static std::shared_ptr<Shader> Create(StringArgs&&... args) noexcept { return std::make_shared<Shader>(std::forward<std::string>(args)...); }

    void BuildFromFile(const std::string& filePath);
    void BuildFromSource(const std::string& vertexSource, const std::string& fragmentSource);

    void Bind() const noexcept;
    void Unbind() const noexcept;
    
    void SetMat4(const std::string& name, const glm::mat4& matrix) const;
    void SetInt(const std::string& name, int value) const;
    void SetBool(const std::string& name, bool value) const;
    void SetFloat(const std::string& name, float value) const;
    void SetFloat3(const std::string& name, const glm::vec3& value) const;

private:
    unsigned int m_RendererID;

private:
    GLint GetUniformLocation(const std::string& name) const;
    std::unordered_map<GLenum, std::string> ParseFile(const std::string& filePath);
};
