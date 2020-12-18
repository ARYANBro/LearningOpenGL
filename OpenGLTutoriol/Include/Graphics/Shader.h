#pragma once

#include "glm/gtc/matrix_transform.hpp"
#include "glad/glad.h"

#include <string>
#include <optional>
#include <unordered_map>

class Shader
{
public:
    Shader() noexcept
         : m_RendererID(0)  {}
         
    Shader(const std::string& vertexSource, const std::string& fragmentSource);
    Shader(const std::string& filePath);
    ~Shader() noexcept;

    void BuildFromFile(const std::string& filePath);
    void BuildFromSource(const std::string& vertexSource, const std::string& fragmentSource);

    void Bind() const noexcept;
    void Unbind() const noexcept;
    
    void SetMat4(const std::string& name, const glm::mat4& matrix);
    void SetInt(const std::string& name, int value);

private:
    unsigned int m_RendererID;

private:
    GLint GetUniformLocation(const std::string& name);
    std::unordered_map<GLenum, std::string> ParseFile(const std::string& filePath);
};
