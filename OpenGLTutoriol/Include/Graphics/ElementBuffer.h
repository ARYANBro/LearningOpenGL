#pragma once

#include <vector>

class ElementBuffer
{
public:
    ElementBuffer(unsigned int* indcies, unsigned int count) noexcept;
    ~ElementBuffer() noexcept;

    void Bind() const noexcept;
    void Unbind() const noexcept;

    void SetData(unsigned int* indcies, unsigned int count) noexcept;

    constexpr unsigned int GetCount() const noexcept { return mCount; }

private:
    unsigned int mRendererID;
    unsigned int mCount;
};
