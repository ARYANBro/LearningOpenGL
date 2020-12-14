#pragma once

#include <vector>
#include <memory>
#include <cassert>

#include "glad/glad.h"

enum class LayoutDataType
{
    Float = 1, Float2 = 2, Float3 = 3
};

class BufferLayout
{
public:
    using ConstIterator = std::vector<LayoutDataType>::const_iterator;
    using Iterator = std::vector<LayoutDataType>::iterator;

public:
    BufferLayout() noexcept;
    BufferLayout(std::initializer_list<LayoutDataType> initList) noexcept;

    ConstIterator begin() const noexcept { return mElements.begin(); }
    ConstIterator end() const noexcept { return mElements.end(); }
    Iterator begin() noexcept { return mElements.begin(); }
    Iterator end() noexcept { return mElements.end(); }
    
    LayoutDataType& operator[](std::size_t index) noexcept
    {
        assert(index <= GetSize());
        return mElements[index];
    }

    const LayoutDataType& operator[](std::size_t index) const noexcept
    {
        assert(index <= GetSize());
        return mElements[index];
    }

    std::size_t GetSize() const { return mElements.size(); }
private:
    std::vector<LayoutDataType> mElements;
};

class VertexBuffer
{
public:
    VertexBuffer(std::size_t size) noexcept;
    explicit VertexBuffer(const void* data, std::size_t size) noexcept;
    ~VertexBuffer() noexcept;

    void Bind() const noexcept;
    void Unbind() const noexcept;

    void SetData(const void* data, std::size_t size) noexcept;
    void SetLayout(const BufferLayout& layout) noexcept { mVertexLayout = layout; }

    constexpr const BufferLayout& GetLayout() const noexcept { return mVertexLayout; }

private:
    unsigned int mRendererID;
    BufferLayout mVertexLayout;

private:
    void AllocateBufferData(const void* data, std::size_t size) noexcept;
};
