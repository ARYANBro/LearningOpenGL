#pragma once

#include "VertexBuffer.h"
#include "ElementBuffer.h"

#include <memory>

class VertexArray
{
public:
    VertexArray() noexcept;
    ~VertexArray() noexcept;

    void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
    void SetElementBuffer(const std::shared_ptr<ElementBuffer>& elementBuffer) noexcept;

    void Bind() const noexcept;
    void Unbind() const noexcept;

    const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const noexcept { return m_VertexBuffers; }
    const std::shared_ptr<VertexBuffer>& GetVertexBuffer(std::size_t index) const noexcept { return m_VertexBuffers.at(index); }
    const std::shared_ptr<ElementBuffer>& GetElementBuffer() const noexcept { return m_ElementBuffer; }

private:
    unsigned int m_RendererID;

    std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
    std::shared_ptr<ElementBuffer> m_ElementBuffer;

private:
    void Delete() noexcept;
    void CalculateOffsetAndStride(const VertexBuffer& vertexBuffer, unsigned int vertexBufferIndex);
};
