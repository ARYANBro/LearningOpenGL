#include "Graphics/Shader.h"

#include "Graphics/RendererAPI.h"

#include "glad/glad.h"

#include <filesystem>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <memory>

static GLenum StringToShaderType(const std::string& shaderName) noexcept
{
    if (shaderName == "vertex")
    {
        return GL_VERTEX_SHADER;
    }
    else if (shaderName == "fragment")
    {
        return GL_FRAGMENT_SHADER;
    }

    assert(false);
    return 0;
}

static std::string RemoveWhiteSpace(const std::string& string) noexcept
{
    std::string result;
    result.reserve(string.size());

    for (const char ch : string)
    {
        if (std::isspace(ch))
        {
            continue;
        }

        result.push_back(ch);
    }

    return result;
}

static std::optional<GLenum> GetShaderTypeFromLine(const std::string& line)
{
    const std::string_view searchPattern = "#shader";

    if (line.find(searchPattern) != std::string::npos)
    {
        std::string shaderName = line.substr(searchPattern.size() + 1);
        shaderName = RemoveWhiteSpace(shaderName);

        return StringToShaderType(shaderName);
    }

    return std::nullopt;
}

Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource)
    : mRendererID(0)
{
    BuildFromSource(vertexSource, fragmentSource);
}

Shader::Shader(const std::string& filePath)
    : mRendererID(0)
{
    BuildFromFile(filePath);
}

Shader::~Shader() noexcept
{
    glDeleteProgram(mRendererID);
}

void Shader::BuildFromSource(const std::string& vertexSource, const std::string& fragmentSource)
{
    assert(!mRendererID);

    GLuint vertexShader;
    GLuint fragmentShader;

    vertexShader = RendererAPI::CreateShader(GL_VERTEX_SHADER, vertexSource.c_str());
    fragmentShader = RendererAPI::CreateShader(GL_FRAGMENT_SHADER, fragmentSource.c_str());
    mRendererID = RendererAPI::CreateShaderProgram(vertexShader, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::BuildFromFile(const std::string& filePath)
{
    assert(!mRendererID);
    const auto shaderSources = ParseFile(filePath);

    mRendererID = glCreateProgram();

    for (const auto& shaderSource : shaderSources)
    {
        const GLuint shader = RendererAPI::CreateShader(shaderSource.first, shaderSource.second.c_str());
        glAttachShader(mRendererID, shader);
    }

    RendererAPI::LinkShaderProgram(mRendererID);
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

void Shader::SetInt(const std::string& name, int value)
{
    glUniform1i(GetUniformLocation(name), value);
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

std::unordered_map<GLenum, std::string> Shader::ParseFile(const std::string& filePath)
{
    std::ifstream inFileStream;
    inFileStream.exceptions(std::ios::badbit);

    std::unordered_map<GLenum, std::string> shaderSources;

    try
    {
        inFileStream.open(filePath);

        std::string line;
        GLenum currentShaderType = 0;

        while (std::getline(inFileStream, line))
        {
            if (const auto newShaderType = GetShaderTypeFromLine(line))
            {
                currentShaderType = newShaderType.value();
            }
            else if (currentShaderType != 0)
            {
                shaderSources[currentShaderType] += line += '\n';
            }
        }
    }
    catch (const std::ifstream::failure& failure)
    {
        throw std::ifstream::failure("Could not read " + filePath + "error code: ", failure.code());
    }
    catch (const std::exception& except)
    {
        throw std::runtime_error("Error in " + filePath + ' ' + except.what());
    }

    return shaderSources;
}