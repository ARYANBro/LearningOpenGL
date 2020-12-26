#include "Graphics/Texture.h"

#include <stb_image.h>
#include <glad/glad.h>

#include <filesystem>
#include <cassert>

void Texture::TextureData::Load(const std::string& filePath) noexcept
{
    stbi_set_flip_vertically_on_load(true);
    Data = stbi_load(filePath.c_str(), &Width, &Height, &NumOfChannels, 0);
    assert(Data);

    if (NumOfChannels == 3)
    {
        Format = GL_RGB;
        InternalFormat = GL_RGB8;
    }
    else if (NumOfChannels == 4)
    {
        Format = GL_RGBA;
        InternalFormat = GL_RGBA8;
    }
    else
    {
        assert(false);
    }
}

Texture::Texture() noexcept
    : m_RendererID(0), m_TextureData()
  
{
    glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
}

Texture::Texture(const std::string& filePath)
    : Texture()

{
    Load(filePath);
}

Texture::~Texture() noexcept
{
    glDeleteTextures(1, &m_RendererID);
    stbi_image_free(m_TextureData.Data);
}

void Texture::Bind(unsigned int slot) noexcept
{
    glBindTextureUnit(slot, m_RendererID);
}

void Texture::Unbind() noexcept
{
    glBindTexture(GL_TEXTURE_2D, 0);    
}

void Texture::Load(const std::string& filePath)
{
    assert(!m_TextureData.Data);

    m_TextureData.Load(filePath);

    Bind();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    UploadData(m_TextureData);
}

void Texture::UploadData(TextureData textureData) noexcept
{
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        textureData.InternalFormat,
        textureData.Width, textureData.Height,
        0,
        textureData.Format,
        GL_UNSIGNED_BYTE,
        textureData.Data
    );

    glGenerateMipmap(GL_TEXTURE_2D);
}
