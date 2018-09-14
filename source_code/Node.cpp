#include "Node.h"

#include <sstream>

namespace kdt
{
    static unsigned int toStringCounter{ 0 };

    /// Default constructor
    /// Takes up to 4 floating point values
    Node::Node(const float x = 0.0f,
               const float y = 0.0f,
               const float z = 0.0f,
               const float w = 1.0f)
        : point{ x, y, z, w }, left{ nullptr }, right{ nullptr }
    {
    }

    /// Overloaded constructor 1
    /// Takes a float4 object
    Node::Node(const float4& p)
        : point{ p }, left{ nullptr }, right{ nullptr }
    {
    }

    /// Overloaded constructor 2
    /// Takes a float4 object, and 2 Node object pointers
    Node::Node(const float4& p, Node *l, Node *r)
        : point{ p }, left{ l }, right{ r }
    {
    }

    /// Destructor
    Node::~Node(void)
    {
        delete left;
        delete right;
    }

    /// Return Node data as a string.
    /// Often used for displaying object information
    /// in console
    std::string Node::ToString(void)
    {
        std::stringstream ss{};

        if (++toStringCounter == 10)
        {
            ss << point.ToString() << std::endl;
            
            toStringCounter = 0;
        }
        else
        {
            ss << point.ToString() << "\t";
        }
        
        return ss.str();
    }

}
