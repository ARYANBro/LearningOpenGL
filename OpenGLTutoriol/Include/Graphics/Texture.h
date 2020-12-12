#pragma once

#include "stb_image.h"
#include "glad/glad.h"

#include <string>
#include <cstddef>
#include <cassert>

class Texture
{
public:
    Texture() noexcept;
    Texture(const std::string& filePath);
    ~Texture() noexcept;

    void Bind(unsigned int slot = 0) noexcept;
    void Unbind() noexcept;

    void Load(const std::string& filePath);

private:
    struct TextureData
    {
        stbi_uc* Data;

        int Width;
        int Height;
        int NumOfChannels;

        GLint InternalFormat;
        GLenum Format;

        void Load(const std::string& filePath) noexcept;
    };

private:
    unsigned int mRendererID;
    TextureData mTextureData;

private:
    void SetData(TextureData textureData) noexcept;
};
