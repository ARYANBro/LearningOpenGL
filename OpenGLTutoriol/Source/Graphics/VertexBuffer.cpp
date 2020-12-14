#include "Graphics/VertexBuffer.h"

#include "Graphics/RendererAPI.h"

#include <numeric>
#include <cassert>

BufferLayout::BufferLayout() noexcept
    : mElements()
{
    GLint maxVertexAttribs;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttribs);

    mElements.reserve(static_cast<std::size_t>(maxVertexAttribs));
}

BufferLayout::BufferLayout(std::initializer_list<LayoutDataType> initList) noexcept
    : BufferLayout()
{
    for (const auto element : initList)
    {
        mElements.push_back(element);
    }
}

VertexBuffer::VertexBuffer(std::size_t size) noexcept
    : mRendererID(RendererAPI::CreateBuffer()),
    mVertexLayout()
{
    AllocateBufferData(nullptr, size);
}

VertexBuffer::VertexBuffer(const void* data, std::size_t size) noexcept
    : mRendererID(RendererAPI::CreateBuffer()),
    mVertexLayout()
{
    AllocateBufferData(data, size);
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

void VertexBuffer::AllocateBufferData(const void* data, std::size_t size) noexcept
{
    Bind();
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(size), data, GL_STATIC_DRAW);
}
