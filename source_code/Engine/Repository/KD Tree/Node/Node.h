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

        Node(const float = 0.0f, const float = 0.0f, const float = 0.0f, const float = 1.0f);
        Node(const Vertex&);
        Node(const Vertex&, Node*, Node*);

        ~Node(void);

#pragma endregion 

#pragma region Geometry helper method

        void IterateNext(std::function<void(Vertex &)>);

#pragma endregion


#pragma region Print methods
        
        std::string ToString(void);

#pragma endregion

    };
}
