#include "pch.h"

#include "KD Tree/Tree/Tree.h"
#include "KD Tree/Vertex/Vertex.h"

#include <string>
#include <vector>

/// namespace KD Tree
namespace kdt
{
    std::string CreateNewTree(std::string);
    std::string CreateNewTree(std::string, vxe::Vertex);
    std::string CreateNewTree(std::string, std::vector<vxe::Vertex>);
    
    void InsertVertexToTree(std::string, vxe::Vertex);
    void InsertVertexToTree(std::string, std::vector<vxe::Vertex>);

    vxe::Tree* GetTree(std::string = "firstTreeAdded");

    std::vector<vxe::Tree*> GetAllTrees(void);
}
