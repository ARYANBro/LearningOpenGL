#pragma once

#include "glad/glad.h"

#include <string>
#include <optional>

class RendererAPI
{
public:
    static std::string GetShaderInfoLog(GLuint shader) noexcept;
    static std::string GetShaderProgramInfoLog(GLuint program) noexcept;

    static std::optional<std::string> GetShaderCompileError(GLenum shader) noexcept;
    static std::optional<std::string> GetShaderProgramError(GLuint program) noexcept;

    static GLuint CreateShader(GLuint type, const char* source);
    static GLuint CreateShaderProgram(GLuint vertexShader, GLuint fragmentShader);
    
    static void LinkShaderProgram(GLuint program);

    static GLuint CreateBuffer() noexcept;
    static GLuint CreateVertexArray() noexcept;
};
