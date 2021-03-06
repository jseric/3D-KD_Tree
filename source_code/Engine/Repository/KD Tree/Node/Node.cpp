#include "pch.h"

#include "Node.h"

#include <DirectXMath.h>
#include <sstream>

namespace vxe
{
    /// Default constructor
    /// Takes up to 4 floating point values
    Node::Node(const float x,
               const float y,
               const float z)
        : point{ x, y, z },
          left{ nullptr }, right{ nullptr }
    {
    }

    /// Overloaded constructor 1
    /// Takes a float4 object
    Node::Node(const DirectX::VertexPosition& p)
        : point{ p }, left{ nullptr }, right{ nullptr }
    {
    }

    /// Overloaded constructor 2
    /// Takes a float4 object, and 2 Node object pointers
    Node::Node(const DirectX::VertexPosition& p, Node *l, Node *r)
        : point{ p }, left{ l }, right{ r }
    {
    }

    /// Destructor
    Node::~Node(void)
    {
        delete left;
        delete right;
    }

    /// Run target method on current point and children
    void Node::IterateNext(std::function<void(DirectX::VertexPosition&)> targetMethod)
    {
        targetMethod(point);

        if (left)
            left->IterateNext(targetMethod);

        if (right)
            right->IterateNext(targetMethod);
    }

    /// Return Node data as a string.
    /// Often used for displaying object information
    /// in console
    std::string Node::ToString(void)
    {
        std::stringstream ss{};
        ss << point.ToString() << std::endl;

        return ss.str();
    }

}
