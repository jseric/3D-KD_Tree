#pragma once

#include "Vertex.h"

#include <string>

/// Namespace KD-Tree
namespace kdt
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
