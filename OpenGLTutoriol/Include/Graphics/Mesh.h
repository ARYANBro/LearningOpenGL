#pragma once

#include "Graphics/VertexArray.h"
#include "Graphics/Shader.h"

#include "glm/gtc/matrix_transform.hpp"

#include <type_traits>

class Mesh
{
public:
    Mesh() noexcept = default;
    Mesh(const std::vector<float>& vertcies, const VertexLayout& layout, const std::shared_ptr<Shader>& shader = std::make_shared<Shader>());
    Mesh(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::vector<float>& vertcies, const std::shared_ptr<Shader>& shader = std::make_shared<Shader>());
    
    void SetIndexData(const std::vector<unsigned int>& indcies) noexcept;
    void SetVertexData(const std::vector<float>& vertcies, const VertexLayout& layout);
    void SetVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);

    void Render() noexcept;
    
    void SetShader(const std::shared_ptr<Shader>& shader) { m_Shader = shader; }
    const std::vector<float>& GetVertexData() const noexcept { return m_VertexData; }
    const VertexArray& GetVertexArray() const noexcept { return m_VertexArray; }
    const std::shared_ptr<Shader>& GetShader() const noexcept { return m_Shader; }

    template<typename MeshType, typename = std::enable_if_t<std::is_base_of_v<Mesh, MeshType>, MeshType>>
    static MeshType Share(const MeshType& mesh);

private:
    std::vector<float> m_VertexData;
    VertexArray m_VertexArray;
    std::shared_ptr<Shader> m_Shader;
};

template<typename MeshType, typename>
MeshType Mesh::Share(const MeshType& mesh) 
{
    return MeshType(mesh.m_VertexArray.GetVertexBuffer(0), mesh.GetVertexData(), mesh.GetShader());
}
