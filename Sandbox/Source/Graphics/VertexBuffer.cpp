#include "Graphics/VertexBuffer.h"

#include "Graphics/RendererAPI.h"

#include <numeric>
#include <cassert>

VertexLayout::VertexLayout()
    : m_Elements()
{
    GLint maxVertexAttribs;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttribs);

    m_Elements.reserve(static_cast<std::size_t>(maxVertexAttribs));
}

VertexLayout::VertexLayout(std::initializer_list<LayoutDataType> initList)
    : VertexLayout()
{
    for (const auto element : initList)
    {
        m_Elements.push_back(element);
    }
}

VertexBuffer::VertexBuffer(std::size_t size) noexcept
    : VertexBuffer(nullptr, size)
{
}

VertexBuffer::VertexBuffer(const void* data, std::size_t size) noexcept
    : m_RendererID(RendererAPI::CreateBuffer()), m_VertexLayout(), m_Size(size)
{
    AllocateBufferData(data, size);
}

VertexBuffer::~VertexBuffer() noexcept
{
    glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Bind() const noexcept
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::Unbind() const noexcept
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::SetBufferData(const void* data, std::size_t size) noexcept
{
    Bind();
    glBufferSubData(GL_ARRAY_BUFFER, 0, static_cast<GLsizeiptr>(size), data);  
}

void VertexBuffer::AllocateBufferData(const void* data, std::size_t size) noexcept
{
    Bind();
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(size), data, GL_STATIC_DRAW);
}
