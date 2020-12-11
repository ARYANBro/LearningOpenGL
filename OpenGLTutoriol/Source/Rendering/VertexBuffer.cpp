#include "Graphics/VertexBuffer.h"

#include "Graphics/RendererAPI.h"

#include <numeric>
#include <cassert>

VertexBuffer::VertexBuffer(std::size_t size) noexcept
    : mRendererID(RendererAPI::CreateBuffer()),
      mVertexLayout()
{
    Bind();
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(size), nullptr, GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer(const void* data, std::size_t size) noexcept
    : mRendererID(RendererAPI::CreateBuffer()),
      mVertexLayout()
{
    Bind();
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(size), data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() noexcept
{
    glDeleteBuffers(1, &mRendererID);
}

void VertexBuffer::Bind() const noexcept
{
    glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
}

void VertexBuffer::Unbind() const noexcept
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::SetData(const void* data, std::size_t size) noexcept
{
    Bind();
    glBufferSubData(GL_ARRAY_BUFFER, 0, static_cast<GLsizeiptr>(size), data);
    
}
