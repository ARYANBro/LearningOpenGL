#pragma once

#include <chrono>

class DeltaTime
{
public:
    using Clock = std::chrono::high_resolution_clock;

public:
    operator float() noexcept
    {
        return m_DeltaTime.count();
    }

private:
    std::chrono::time_point<Clock> m_LastFrameTime;
    std::chrono::duration<float> m_DeltaTime;

private:
    void Calculate() noexcept;

private:
    friend class Application;
};
