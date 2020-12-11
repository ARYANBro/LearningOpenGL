#pragma once

#include "VertexBuffer.h"
#include "ElementBuffer.h"

#include <memory>

class VertexArray
{
public:
    VertexArray() noexcept;
    ~VertexArray() noexcept;

    void AddVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuff) noexcept;
    void SetElementBuffer(std::shared_ptr<ElementBuffer> elementBuff) noexcept;

    void Bind() const noexcept;
    void Unbind() const noexcept;

    constexpr const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const noexcept{ return mVertexBuffers; }
    constexpr const std::shared_ptr<ElementBuffer>& GetElementBuffer() const noexcept { return mElementBuffer; }

private:
    unsigned int mRendererID;

    std::vector<std::shared_ptr<VertexBuffer>> mVertexBuffers;
    std::shared_ptr<ElementBuffer> mElementBuffer;
};
