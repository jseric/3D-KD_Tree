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
    };
}
