#pragma once

#include "pch.h"

#include "../Node/Node.h"
#include "../Root/Root.h"
#include "../Vertex/Vertex.h"

#include <string>
#include <vector>

namespace vxe
{
    class Tree
    {
    private:
#pragma region Private members

        Root root;

#pragma endregion

#pragma region Private helper methods

        Node* CreateNewNode(const DirectX::VertexPosition&);

        void InitTreeWithMultiplePoints(std::vector<DirectX::VertexPosition>);

        unsigned int GetIndexOfMedianNode(std::vector<DirectX::VertexPosition>&);

        void ReadFromFile(std::string&);

        void IncrementDimension(unsigned int&);

        void DeleteAll(Node*);

        int Delete(DirectX::VertexPosition&, Node*, unsigned int);

        DirectX::VertexPosition FindMin(Node*, unsigned int, unsigned int);

        DirectX::VertexPosition FindMax(Node*, unsigned int, unsigned int);

        void NearestNeighbourSearch(DirectX::VertexPosition&, Node*,
            unsigned int, DirectX::VertexPosition&, float&);

        std::string ToString(Node*);

#pragma endregion

    public:
#pragma region Constructors and destructor

        Tree(void);
        Tree(const DirectX::VertexPosition&);
        Tree(std::vector<DirectX::VertexPosition>);
        Tree(std::string&);

        ~Tree(void);

#pragma endregion

#pragma region Public tree methods

        int Insert(DirectX::VertexPosition&);
        int Insert(std::vector<DirectX::VertexPosition>&);

        int Delete(DirectX::VertexPosition&);

        DirectX::VertexPosition NearestNeighbourSearch(DirectX::VertexPosition&);

        bool Find(DirectX::VertexPosition&);

#pragma endregion

#pragma region Geometry helper method

        void Foreach(std::function<void(DirectX::VertexPosition &)>);

#pragma endregion


#pragma region Print methods

        std::string ToString(void);

#pragma endregion

#pragma region Static methods

        static void SortPointsByXValue(std::vector<DirectX::VertexPosition>&);

        static bool SortByXCriterion(DirectX::VertexPosition&, DirectX::VertexPosition&);

#pragma endregion 

    };
}
