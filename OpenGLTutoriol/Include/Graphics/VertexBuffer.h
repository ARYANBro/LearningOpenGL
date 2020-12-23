#pragma once

#include <vector>
#include <memory>
#include <cassert>

#include "glad/glad.h"

enum class LayoutDataType
{
    Float = 1, Float2 = 2, Float3 = 3
};

class VertexLayout
{
public:
    using ConstIterator = std::vector<LayoutDataType>::const_iterator;
    using Iterator = std::vector<LayoutDataType>::iterator;

public:
    VertexLayout();
    VertexLayout(std::initializer_list<LayoutDataType> initList);

    std::size_t GetSize() const noexcept { return m_Elements.size(); }
    ConstIterator begin() const noexcept { return m_Elements.begin(); }
    ConstIterator end() const noexcept { return m_Elements.end(); }
    Iterator begin() noexcept { return m_Elements.begin(); }
    Iterator end() noexcept { return m_Elements.end(); }
    
    LayoutDataType& operator[](std::size_t index) noexcept
    {
        assert(index <= GetSize());
        return m_Elements[index];
    }

    const LayoutDataType& operator[](std::size_t index) const noexcept
    {
        assert(index <= GetSize());
        return m_Elements[index];
    }

private:
    std::vector<LayoutDataType> m_Elements;
};

class VertexBuffer
{
public:
    VertexBuffer(std::size_t size) noexcept;
    explicit VertexBuffer(const void* data, std::size_t size) noexcept;
    ~VertexBuffer() noexcept;

    void Bind() const noexcept;
    void Unbind() const noexcept;

    void SetBufferData(const void* data, std::size_t size) noexcept;
    void SetLayout(const VertexLayout& layout) noexcept { m_VertexLayout = layout; }

    const VertexLayout& GetLayout() const noexcept { return m_VertexLayout; }
    std::size_t GetVertexCount() const noexcept { return m_Size / sizeof(float); }
    std::size_t GetSize() const noexcept { return m_Size; }
    
private:
    unsigned int m_RendererID;
    VertexLayout m_VertexLayout;
    std::size_t m_Size;

private:
   friend class VertexArray;

private:
    void AllocateBufferData(const void* data, std::size_t size) noexcept;
};
