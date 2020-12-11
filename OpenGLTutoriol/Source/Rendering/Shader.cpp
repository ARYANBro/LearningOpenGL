#include "Graphics/Shader.h"

#include "Graphics/RendererAPI.h"

#include "glad/glad.h"

#include <iostream>
#include <unordered_map>
#include <memory>
#include <stdexcept>

Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource)
    : mRendererID(0)
{
    BuildShaders(vertexSource, fragmentSource);
}

Shader::~Shader() noexcept
{
    glDeleteProgram(mRendererID);
}

void Shader::BuildShaders(const std::string& vertexSource, const std::string& fragmentSource)
{
    GLuint vertexShader;
    GLuint fragmentShader;

    try
    {
        vertexShader = RendererAPI::CreateShaderFromSource(GL_VERTEX_SHADER, vertexSource.c_str());
        fragmentShader = RendererAPI::CreateShaderFromSource(GL_FRAGMENT_SHADER, fragmentSource.c_str());
        mRendererID = RendererAPI::CreateShaderProgramFromShaders(vertexShader, fragmentShader);

        std::cerr << "Shader::BuildShaders()::vertexShader: " << vertexShader << std::endl;
        std::cerr << "Shader::BuildShaders()::fragmentShadr: " << fragmentShader << std::endl;
        std::cerr << "Shader::mRendererID: " << mRendererID << std::endl;

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
    catch (const std::exception&)
    {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        throw;
    }
}

void Shader::Bind() const noexcept
{
    glUseProgram(mRendererID);
}

void Shader::Unbind() const noexcept
{
    glUseProgram(0);
}

void Shader::SetMat4(const std::string& name, const glm::mat4& matrix)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

GLint Shader::GetUniformLocation(const std::string& name)
{
    GLint location = glGetUniformLocation(mRendererID, name.c_str());

    if (location == -1)
    {
        throw std::runtime_error(name + " not found");
    }

    return location;
}
