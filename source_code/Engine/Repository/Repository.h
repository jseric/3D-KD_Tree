#include "pch.h"

#include "KD Tree/Tree/Tree.h"
#include "KD Tree/Vertex/Vertex.h"

#include <string>
#include <vector>

/// namespace KD Tree
namespace kdt
{
    std::string CreateNewTree(std::string);
    std::string CreateNewTree(std::string, DirectX::VertexPosition);
    std::string CreateNewTree(std::string, std::vector<DirectX::VertexPosition >);
    
    void InsertVertexToTree(std::string, DirectX::VertexPosition);
    void InsertVertexToTree(std::string, std::vector<DirectX::VertexPosition>);

    vxe::Tree* GetTree(std::string = "firstTreeAdded");

    std::vector<vxe::Tree*> GetAllTrees(void);
}
