#include "Graphics/Mesh.h"

#include "Graphics/VertexBuffer.h"

#include "glad/glad.h"

Mesh::Mesh(const std::vector<float>& vertcies, const VertexLayout& layout, const std::shared_ptr<Shader>& shader)
    : m_VertexData(vertcies), m_VertexArray(), m_Shader(shader)
{
    SetVertexData(vertcies, layout);
}

Mesh::Mesh(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::vector<float>& vertcies, const std::shared_ptr<Shader>& shader)
    : m_VertexData(vertcies), m_VertexArray(), m_Shader(shader)
{
    SetVertexBuffer(vertexBuffer);
}

// TODO: Testing
void Mesh::SetIndexData(const std::vector<unsigned int>& indcies) noexcept
{
    const auto elementBuffer = std::make_shared<ElementBuffer>(indcies.data(), indcies.size());
    m_VertexArray.SetElementBuffer(elementBuffer);
}

void Mesh::SetVertexData(const std::vector<float>& vertcies, const VertexLayout& layout)
{
    const auto vertexBuffer = std::make_shared<VertexBuffer>(vertcies.data(), vertcies.size() * sizeof(float));
    vertexBuffer->SetLayout(layout);

    m_VertexArray.AddVertexBuffer(vertexBuffer);
}

void Mesh::SetVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
{
    // Make sure no vertex buffer is bound as it doesn't make sense to have more than one vertex buffers bound to a mesh
    assert(m_VertexArray.GetVertexBuffers().empty());
    m_VertexArray.AddVertexBuffer(vertexBuffer);
}

void Mesh::Render() noexcept
{
    m_Shader->Bind();
    m_VertexArray.Bind();

    glDrawArrays(GL_TRIANGLES, 0, m_VertexArray.GetVertexBuffer(0)->GetVertexCount());
}
