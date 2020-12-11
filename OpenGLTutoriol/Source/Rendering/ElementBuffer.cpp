#include "Graphics/ElementBuffer.h"

#include "Graphics/RendererAPI.h"

#include <iostream>
#include <cassert>

ElementBuffer::ElementBuffer(unsigned int* indcies, unsigned int count) noexcept
    : mRendererID(RendererAPI::CreateBuffer()),
      mCount(count)
{
    assert(indcies);

    int index;
    for (auto iter = indcies; iter != indcies + count; iter++)
    {
        std::cerr << "ElementBuffer::ElementBuffer::indcies[" << index << "]: " << *iter << std::endl;
        index++;
    }

    std::cerr << "ElementBuffer::mRendererID: " << mRendererID << std::endl;
    std::cerr << "ElementBuffer::mCount: " << mCount<< std::endl;

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

void ElementBuffer::SetData(unsigned int* indcies, unsigned int count) noexcept
{
    int index;
    for (auto iter = indcies; iter != indcies + count; iter++)
    {
        std::cerr << "ElementBuffer::ElementBuffer::indcies[" << index << "]: " << *iter << std::endl;
        index++;
    }
    std::cerr << "ElementBuffer::SetData()::count: " << count << std::endl;

    assert(indcies);

    Bind();
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, static_cast<GLsizeiptr>(count * sizeof(unsigned int)), indcies);

    mCount = count;
}
