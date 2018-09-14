#pragma once

#include "Node.h"

/// Namespace KD-Tree
namespace kdt
{
    /// Root element of KDTree
    struct Root
    {
        /// Members
        Node* next;

        /// Constructor
        Root(Node* node = nullptr)
            : next{ node }
        {
        }
    };
}
