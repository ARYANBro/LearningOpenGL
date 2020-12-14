#pragma once

#include <vector>

class ElementBuffer
{
public:
    ~ElementBuffer() noexcept;
    ElementBuffer(const unsigned int* indcies, unsigned int count) noexcept;

    void Bind() const noexcept;
    void Unbind() const noexcept;
    
    void SetData(const unsigned int* indcies, unsigned int count) noexcept;

    constexpr unsigned int GetCount() const noexcept { return mCount; }

private:
    unsigned int mRendererID;
    unsigned int mCount;
};
