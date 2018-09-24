#pragma once

#include "pch.h"

#include "../Node/Node.h"

namespace vxe
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

        /// For each method helper
        /// Run target method on next member
        void RunOnNode(std::function<void(Vertex &point)> targetMethod)
        {
            if (next)
                next->IterateNext(targetMethod);
        }
    };
}
