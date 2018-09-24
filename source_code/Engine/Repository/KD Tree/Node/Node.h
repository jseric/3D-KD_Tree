#pragma once

#include "pch.h"

#include "../Vertex/Vertex.h"

#include <string>

namespace vxe
{
    struct Node
    {
#pragma region Members

        Vertex point;
        
        Node* left;
        Node* right;

#pragma endregion

#pragma region Constructors and destructor

        Node(const float, const float, const float, const float);
        Node(const Vertex&);
        Node(const Vertex&, Node*, Node*);

        ~Node(void);

#pragma endregion 

#pragma region Print methods
        
        std::string ToString(void);

#pragma endregion

    };
}
