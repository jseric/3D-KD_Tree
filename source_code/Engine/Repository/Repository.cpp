#include "pch.h"

#include "Repository.h"

#include "../Utilities.h"
#include "Utilities.h"

#include <map>
#include <sstream>

namespace kdt
{

    /// Repository global variable, only accessible
    /// inside this file
    static std::map<std::string, std::shared_ptr<vxe::Tree>> repo;


    /// Private method
    /// Get a unique name for the new tree object
    static std::string CreateUniqueName(std::string name)
    {
        unsigned int i{ 0 };
        std::stringstream target{ name };

        while (kdt::GetTree(target.str()))
        {
            i++;

            target.str("");
            target << name << i;
        }

        return target.str();
    }


    /// Create new empty tree
    std::string CreateNewTree(std::string name)
    {
        std::string targetName{ CreateUniqueName(name) };
        repo[targetName] = std::make_shared<vxe::Tree>(targetName);

        return targetName;
    }

    /// Create new tree and add 1 vertex
    std::string CreateNewTree(std::string name, DirectX::VertexPosition vertex)
    {
        std::string targetName{ CreateUniqueName(name) };
        repo[targetName] = std::shared_ptr<vxe::Tree>(new vxe::Tree(vertex));

        return targetName;
    }

    /// Create new tree and add multiple vertices
    std::string CreateNewTree(std::string name, 
        std::vector<DirectX::VertexPosition> vertices)
    {
        std::string targetName{ CreateUniqueName(name) };
        repo[targetName] = std::shared_ptr<vxe::Tree>(new vxe::Tree(vertices));

        return targetName;
    }

    /// Insert a vertex into the target tree
    void InsertVertexToTree(std::string targetName,
        DirectX::VertexPosition vertex)
    {
        vxe::Tree* target = kdt::GetTree(targetName);

        if (!target)
        {
            // Target tree not found

            vxe::DebugPrint(std::string("\t Tree repository: No tree with string value found... \n"));
            return;
        }

        target->Insert(vertex);
    }

    /// Insert multiple vertices into the target tree
    void InsertVertexToTree(std::string targetName,
        std::vector<DirectX::VertexPosition> vertices)
    {
        vxe::Tree* target = kdt::GetTree(targetName);

        if (!target)
        {
            // Target tree not found

            vxe::DebugPrint(std::string("\t Tree repository: No tree with string value found... \n"));
            return;
        }

        target->Insert(vertices);
    }

    /// Get the target tree
    vxe::Tree* GetTree(std::string targetName)
    {
        if (targetName == "firstTreeAdded")
            return repo[0].get();

        auto& query = repo.find(targetName);

        return query == repo.end() ? nullptr : query->second.get();
    }

    /// Get all trees from repository
    std::vector<vxe::Tree*> GetAllTrees(void)
    {
        std::vector<vxe::Tree*> target;

        for (auto& tree : repo)
            target.push_back(tree.second.get());

        return target;
    }
};
