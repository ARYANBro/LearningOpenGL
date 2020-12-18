#include "DeltaTime.h"

void DeltaTime::Calculate() noexcept
{
    const auto currentTime = Clock::now();

    m_DeltaTime = currentTime - m_LastFrameTime;
    m_LastFrameTime = currentTime;
}
