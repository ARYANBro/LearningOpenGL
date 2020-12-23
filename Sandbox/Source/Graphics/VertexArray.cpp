#include "Graphics/VertexArray.h"

#include "Graphics/RendererAPI.h"

#include "Graphics/VertexBuffer.h"
#include "Graphics/ElementBuffer.h"

#include <numeric>
#include <iostream>
#include <memory>

VertexArray::VertexArray() noexcept
    : m_RendererID(RendererAPI::CreateVertexArray()), m_VertexBuffers(), m_ElementBuffer(nullptr)
{
}

VertexArray::~VertexArray() noexcept
{
    Delete();
}

void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
{
    Bind();

    try
    {
        CalculateOffsetAndStride(*vertexBuffer, m_VertexBuffers.size());
        m_VertexBuffers.push_back(vertexBuffer);
    }
    catch (...)
    {
        Unbind();
        Delete();

        throw;
    }
}

void VertexArray::SetElementBuffer(const std::shared_ptr<ElementBuffer>& elementBuffer) noexcept
{
    Bind();
    elementBuffer->Bind();
    m_ElementBuffer = elementBuffer;
}

void VertexArray::Bind() const noexcept
{
    glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const noexcept
{
    glBindVertexArray(0);
}

void VertexArray::Delete() noexcept
{
    glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::CalculateOffsetAndStride(const VertexBuffer& vertexBuffer, unsigned int vertexBufferIndex)
{
    const VertexLayout layout = vertexBuffer.GetLayout();

    GLsizei stride = std::accumulate(layout.begin(), layout.end(), 0, [](GLsizei init, LayoutDataType type) { return init + static_cast<GLsizei>(type); });
    stride *= static_cast<GLsizei>(sizeof(GLfloat));

    GLsizeiptr attribOffset = 0;

    for (GLuint i = 0; i < layout.GetSize(); i++)
    {
        glEnableVertexAttribArray(i);
        glBindVertexBuffer(vertexBufferIndex, vertexBuffer.m_RendererID, 0, stride);

        const GLint attribSize = static_cast<GLint>(layout[i]);
        glVertexAttribFormat(i, attribSize, GL_FLOAT, GL_FALSE, attribOffset);
        glVertexAttribBinding(i, vertexBufferIndex);

        attribOffset += static_cast<GLsizeiptr>(attribSize) * static_cast<GLsizeiptr>(sizeof(GLfloat));
    }
}
