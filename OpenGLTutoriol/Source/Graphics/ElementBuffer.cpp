#include "Graphics/ElementBuffer.h"

#include "Graphics/RendererAPI.h"

#include <iostream>
#include <cassert>

ElementBuffer::ElementBuffer(const unsigned int* indcies, unsigned int count) noexcept
    : mRendererID(RendererAPI::CreateBuffer()),
    mCount(count)
{
    assert(indcies);

    Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(count * sizeof(unsigned int)), indcies, GL_STATIC_DRAW);
}

ElementBuffer::~ElementBuffer() noexcept
{
    glDeleteBuffers(1, &mRendererID);
}

void ElementBuffer::Bind() const noexcept
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
}

void ElementBuffer::Unbind() const noexcept
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ElementBuffer::SetData(const unsigned int* indcies, unsigned int count) noexcept
{
    assert(indcies);

    Bind();
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, static_cast<GLsizeiptr>(count * sizeof(unsigned int)), indcies);

    mCount = count;
}
