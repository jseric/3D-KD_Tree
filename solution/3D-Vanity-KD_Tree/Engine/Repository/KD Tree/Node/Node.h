#pragma once

#include "pch.h"

#include "../Vertex/Vertex.h"

#include <string>

namespace vxe
{
    struct Node
    {
#pragma region Members

        DirectX::VertexPosition point;
        
        Node* left;
        Node* right;

#pragma endregion

#pragma region Constructors and destructor

        Node(const float = 0.0f, const float = 0.0f, const float = 0.0f);
        Node(const DirectX::VertexPosition&);
        Node(const DirectX::VertexPosition&, Node*, Node*);

        ~Node(void);

#pragma endregion 

#pragma region Geometry helper method

        void IterateNext(std::function<void(DirectX::VertexPosition &)>);

#pragma endregion


#pragma region Print methods
        
        std::string ToString(void);

#pragma endregion

    };
}
