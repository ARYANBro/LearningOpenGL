#include "Graphics/VertexArray.h"

#include "Graphics/RendererAPI.h"

#include "Graphics/VertexBuffer.h"
#include "Graphics/ElementBuffer.h"

#include <numeric>
#include <iostream>
#include <memory>

static void CalculateOffsetAndStride(const BufferLayout& layout)
{
    GLsizei stride = std::accumulate(layout.begin(), layout.end(), 0, [](GLsizei init, LayoutDataType type)
    {
        return init + static_cast<GLsizei>(type);
    });

    stride *= static_cast<GLsizei>(sizeof(GLfloat));

    GLsizeiptr attribOffset = 0;

    for (GLuint i = 0; i < layout.GetSize(); i++)
    {
        glEnableVertexAttribArray(i);

        const GLint attribSize = static_cast<GLint>(layout[i]);
        glVertexAttribPointer(i, attribSize, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<const void*>(attribOffset));

        attribOffset += static_cast<GLsizeiptr>(attribSize) * static_cast<GLsizeiptr>(sizeof(GLfloat));
    }
}

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
    vertexBuffer->Bind();

    try
    {
        CalculateOffsetAndStride(vertexBuffer->GetLayout());
        m_VertexBuffers.push_back(vertexBuffer);
    }
    catch (...)
    {
        Unbind();
        vertexBuffer->Unbind();
        Delete();

        throw std::runtime_error("Could not calculate vertex attribute's offsets and stride");
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
