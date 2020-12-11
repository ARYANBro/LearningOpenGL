#pragma once

#include "glm/gtc/matrix_transform.hpp"
#include "glad/glad.h"

#include <string>
#include <optional>

class Shader
{
public:
    Shader() noexcept = default;
    Shader(const std::string& vertexSource, const std::string& fragmentSource);
    ~Shader() noexcept;

    // TODO: Add file support

    void BuildShaders(const std::string& vertexSource, const std::string& fragmentSource);

    void Bind() const noexcept;
    void Unbind() const noexcept;
    
    void SetMat4(const std::string& name, const glm::mat4& matrix);

private:
    unsigned int mRendererID;

private:
    GLint GetUniformLocation(const std::string& name);
};
