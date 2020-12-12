#pragma once

#include "glad/glad.h"

#include <string>
#include <optional>
#include <memory>

class RendererAPI
{
public:
    static std::string GetShaderInfoLog(GLuint shader) noexcept;
    static std::string GetShaderProgramInfoLog(GLuint program) noexcept;

    // These function return a string if an error occured
    static std::optional<std::string> ValidateShaderCompilation(GLenum shader) noexcept;
    static std::optional<std::string> ValidateShaderProgram(GLuint program) noexcept;

    static GLuint CreateShaderFromSource(GLuint type, const char* source);
    static GLuint CreateShaderProgramFromShaders(GLuint vertexShader, GLuint fragmentShader);
    
    static void LinkShaderProgram(GLuint program);

    static GLuint CreateBuffer() noexcept;
    static GLuint CreateVertexArray() noexcept;

    static std::optional<std::string> ShaderTypeToString(GLenum shaderType) noexcept;
    static std::optional<GLenum> StringToShaderType(const std::string& shaderName) noexcept;
};
