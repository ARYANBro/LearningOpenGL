#pragma once

#include "Graphics/Mesh.h"

#include "glm/gtc/matrix_transform.hpp"

#include <functional>
#include <memory>
#include <string>
#include <array>

class CubeMesh : public Mesh
{
public:
    CubeMesh(const std::shared_ptr<Shader>& shader = Shader::Create());

    CubeMesh(const Mesh& cube);
    
private:
    using Mesh::SetVertexData;
    using Mesh::SetIndexData;

private:
    template<typename MeshType, typename>
    friend MeshType Mesh::Share(const MeshType& mesh);
};
