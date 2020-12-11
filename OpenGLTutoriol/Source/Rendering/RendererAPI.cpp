#include "Graphics/RendererAPI.h"

#include "Graphics/Shader.h"

#include <unordered_map>
#include <stdexcept>
#include <cassert>
#include <memory>

using GetivFunction = void (*)(GLuint, GLenum, GLint*);
using GetInfoLogFunction = void (*)(GLuint, GLsizei, GLsizei*, GLchar*);

static std::string GetInfoLog(GLuint object, const GetivFunction& getivFunction, const GetInfoLogFunction& getInfoLogFunction) noexcept
{
    assert(object != 0);
    GLint logLength;
    getivFunction(object, GL_INFO_LOG_LENGTH, &logLength);

    const auto logInfo = std::make_unique<GLchar[]>(static_cast<size_t>(logLength));
    GLchar* logInfoData = logInfo.get();
        
    getInfoLogFunction(object, logLength, nullptr, logInfoData);

    return logInfoData;
}

static std::optional<const char*> GetShaderTypeString(GLenum shaderType) noexcept
{
    static const std::unordered_map<GLenum, const char*> sShaderNames = {
        { GL_VERTEX_SHADER, "Vertex Shader" },
        { GL_FRAGMENT_SHADER, "Fragment Shadre" }
    };

    if (const auto shaderName = sShaderNames.find(shaderType); shaderName != sShaderNames.end())
    {
        return shaderName->second;
    }

    return std::nullopt;
}

std::string RendererAPI::GetShaderInfoLog(GLuint shader) noexcept
{
    assert(shader != 0);
    return GetInfoLog(shader, glGetShaderiv, glGetShaderInfoLog);
}

std::string RendererAPI::GetShaderProgramInfoLog(GLuint shaderProgram) noexcept
{
    assert(shaderProgram != 0);
    return GetInfoLog(shaderProgram, glGetShaderiv, glGetShaderInfoLog);
}

std::optional<std::string> RendererAPI::ValidateShaderCompilation(GLenum shader) noexcept
{
    assert(shader != 0);
    
    GLint compileStatus;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);

    if (!compileStatus)
    {
        return GetShaderInfoLog(shader);
    }

    return std::nullopt;
}

std::optional<std::string> RendererAPI::ValidateShaderProgram(GLuint shaderProgram) noexcept
{
    assert(shaderProgram != 0);
    glValidateProgram(shaderProgram);

    GLint validateStatus;
    glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &validateStatus);

    if (!validateStatus)
    {
        return GetShaderProgramInfoLog(shaderProgram);
    }
    
    return std::nullopt;
}

GLuint RendererAPI::CreateShaderFromSource(GLenum type, const char* source)
{
    assert(source);
    GLuint shader = glCreateShader(type);

    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    if (auto error = ValidateShaderCompilation(shader))
    {
        glDeleteShader(shader);

        auto shaderType = GetShaderTypeString(type);
        throw std::runtime_error(shaderType.value_or("null") + std::string(" compilition failed\n") + error.value());
    }

    return shader;
}

GLuint RendererAPI::CreateShaderProgramFromShaders(GLuint vertexShader, GLuint fragmentShader)
{
    GLuint shaderProgram;

    try
    {
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);

        LinkShaderProgram(shaderProgram);

        return shaderProgram;
    }
    catch (const std::exception&)
    {
        glDeleteProgram(shaderProgram);
        throw;
    }
}

void RendererAPI::LinkShaderProgram(GLuint shaderProgram)
{
    assert(shaderProgram);

    glLinkProgram(shaderProgram);

    if (auto error = ValidateShaderProgram(shaderProgram))
    {
        throw std::runtime_error("Program failed to link\n" + error.value());
    }

}

GLuint RendererAPI::CreateBuffer() noexcept
{
    GLuint buffer;
    glCreateBuffers(1, &buffer);

    return buffer;
}

GLuint RendererAPI::CreateVertexArray() noexcept
{
    GLuint vao;
    glCreateVertexArrays(1, &vao);

    return vao;
}
