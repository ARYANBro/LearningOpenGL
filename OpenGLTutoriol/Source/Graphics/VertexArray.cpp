#include "Graphics/VertexArray.h"

#include "Graphics/RendererAPI.h"

#include "Graphics/VertexBuffer.h"
#include "Graphics/ElementBuffer.h"

#include <numeric>
#include <iostream>
#include <memory>

static void CalculateOffsetAndStride(const BufferLayout& layout) noexcept
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
    : mRendererID(RendererAPI::CreateVertexArray())
{
}

VertexArray::~VertexArray() noexcept
{
    glDeleteVertexArrays(1, &mRendererID);
}

void VertexArray::AddVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer) noexcept
{
    Bind();
    vertexBuffer->Bind();

    CalculateOffsetAndStride(vertexBuffer->GetLayout());

    mVertexBuffers.push_back(vertexBuffer);
}

void VertexArray::SetElementBuffer(std::shared_ptr<ElementBuffer> elementBuffer) noexcept
{
    Bind();
    elementBuffer->Bind();
    mElementBuffer = elementBuffer;
}

void VertexArray::Bind() const noexcept
{
    glBindVertexArray(mRendererID);
}

void VertexArray::Unbind() const noexcept
{
    glBindVertexArray(0);
}
