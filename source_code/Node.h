#pragma once

#include "Vector4.h"

#include <string>

/// Namespace KD-Tree
namespace kdt
{
    struct Node
    {
#pragma region Members

        float4 point;
        
        Node* left;
        Node* right;

#pragma endregion

#pragma region Constructors and destructor

        Node(const float, const float, const float, const float);
        Node(const float4&);
        Node(const float4&, Node*, Node*);

        ~Node(void);

#pragma endregion 

#pragma region Print methods
        
        std::string ToString(void);

#pragma endregion

    };
}
