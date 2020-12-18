#include "Graphics/RendererAPI.h"

#include <unordered_map>
#include <stdexcept>
#include <cassert>
#include <memory>

static std::string ShaderTypeToString(GLenum shaderType) noexcept
{
    switch (shaderType)
    {
    case GL_VERTEX_SHADER:
        return "vertex";
    
    case GL_FRAGMENT_SHADER:
        return "fragment";

    default:
        return "null";
        assert(false);
    }
}

static std::string GetInfoLog(GLuint object, void (*getivFunction)(GLuint, GLenum, GLint*), void (*getInfoLogFunction)(GLuint, GLsizei, GLsizei*, GLchar*))
{
    assert(object != 0);
    GLint logLength;
    getivFunction(object, GL_INFO_LOG_LENGTH, &logLength);

    const auto logInfo = std::make_unique<GLchar[]>(static_cast<size_t>(logLength));
    GLchar* logInfoData = logInfo.get();
        
    getInfoLogFunction(object, logLength, nullptr, logInfoData);

    return logInfoData;
}

std::string RendererAPI::GetShaderInfoLog(GLuint shader) noexcept
{
    assert(shader != 0);

    try
    {
       return GetInfoLog(shader, glGetShaderiv, glGetShaderInfoLog);
    }
    catch (const std::exception& except)
    {
        return "null";
    }
}

std::string RendererAPI::GetShaderProgramInfoLog(GLuint shaderProgram) noexcept
{
    assert(shaderProgram != 0);

    try
    {
        return GetInfoLog(shaderProgram, glGetShaderiv, glGetShaderInfoLog);
    }
    catch (const std::exception& except)
    {
        return "null";
    }
}

std::optional<std::string> RendererAPI::GetShaderCompileError(GLenum shader) noexcept
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

std::optional<std::string> RendererAPI::GetShaderProgramError(GLuint shaderProgram) noexcept
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

GLuint RendererAPI::CreateShader(GLenum type, const char* source)
{
    assert(source);
    assert(type == GL_VERTEX_SHADER || type == GL_FRAGMENT_SHADER);
    
    GLuint shader = glCreateShader(type);

    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    if (const auto error = GetShaderCompileError(shader))
    {
        glDeleteShader(shader);

        auto shaderType = ShaderTypeToString(type);
        throw std::runtime_error(shaderType + std::string(" shader compilition failed\n") + error.value() + "\n\n" + source);
    }

    return shader;
}

GLuint RendererAPI::CreateShaderProgram(GLuint vertexShader, GLuint fragmentShader)
{
    assert(vertexShader != 0 && fragmentShader != 0);

    GLuint shaderProgram;

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    LinkShaderProgram(shaderProgram);

    return shaderProgram;
}

void RendererAPI::LinkShaderProgram(GLuint shaderProgram)
{
    assert(shaderProgram);

    glLinkProgram(shaderProgram);

    if (auto error = GetShaderProgramError(shaderProgram))
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
