#pragma once

#include "Application.h"

#include "Graphics/VertexArray.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"

class OpenGLApplication : public Application
{    
public:
    OpenGLApplication(int windowWidth, int windowHeight) noexcept
        : Application(windowWidth, windowHeight, "OpenGLApplication")
    {
    }

    virtual void OnBegin() noexcept override;
    virtual void OnUpdate() noexcept override;
    virtual void OnRender() noexcept override;

private:
    VertexArray mVao;
    
    Shader mShader;
    Texture mFabricTexture;
    Texture mPavingStonesTexture;

    glm::mat4 mModelMatrix;
    glm::mat4 mViewMatrix;
    glm::mat4 mProjectionMatrix;

private:
    void LoadAssets() noexcept;
};
