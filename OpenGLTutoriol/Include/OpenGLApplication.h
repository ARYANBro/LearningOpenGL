#pragma once

#include "Application.h"

#include "Graphics/VertexBuffer.h"
#include "Graphics/ElementBuffer.h"
#include "Graphics/VertexArray.h"
#include "Graphics/Shader.h"

class OpenGLApplication : public Application
{
public:
    virtual void OnBegin() noexcept override;
    virtual void OnUpdate() noexcept override;
    virtual void OnRender() noexcept override;

private:
    VertexArray mVao;
    
    Shader mShader;
};
