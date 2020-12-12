#pragma once

#include "Application.h"

#include "Graphics/VertexArray.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"

class OpenGLApplication : public Application
{
public:
    virtual void OnBegin() noexcept override;
    virtual void OnUpdate() noexcept override;
    virtual void OnRender() noexcept override;

private:
    VertexArray mVao;
    
    Shader mShader;
    Texture mFabricTexture;
    Texture mPavingStonesTexture;

private:
    void InitBuffers() noexcept;
    void LoadAssets() noexcept;
};
