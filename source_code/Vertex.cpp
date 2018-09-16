#include "Vertex.h"

#include <cmath>
#include <sstream>

/// Namespace KD-Tree
namespace kdt
{
    /// Default constructor
    /// Takes up to 8 float arguments
    Vertex::Vertex(const float x, const float y,
                   const float z, const float w,
                   const float r, const float g,
                   const float b, const float a)
        : position{ DirectX::XMFLOAT4{ x, y, z, w } },
          color{    DirectX::XMFLOAT4{ r, g, b, a } }
    {
    }

    /// Constructor
    /// Takes 2 DirectX::XMFLOAT4 arguments 
    Vertex::Vertex(
        DirectX::XMFLOAT4& pos,
        DirectX::XMFLOAT4& col)
        : position{ pos }, color{ col }
    {
    }

    /// Overloaded operator []
    ///
    /// Allows the members of object to be
    /// accessible as array members
    ///
    /// Example: obj.x is the same as obj[0]
    float& Vertex::operator[](unsigned int index)
    {
        switch (index % 8)
        {
        case 0:
            return position.x;
        case 1:
            return position.y;
        case 2:
            return position.z;
        case 3:
            return position.w;

        case 4:
            return color.x;
        case 5:
            return color.y;
        case 6:
            return color.z;
        case 7:
            return color.w;

        default:
            return position.x;
        }
    }

    std::string Vertex::ToString(void)
    {
        std::stringstream ss{};

        ss << "Position: ";
        ss << "[ " << position.x << " " << position.y;
        ss << " " << position.z << " " << position.w;
        ss << " ]" << std::endl;

        ss << "Color: ";
        ss << "[ " << position.x << " " << position.y;
        ss << " " << position.z << " " << position.w;
        ss << " ]" << std::endl;

        return ss.str();
    }

    /// Overloaded operator =
    void Vertex::operator=(Vertex v)
    {
        position = v.position;
        color    = v.color;
    }



    /// Compare 2 vectors
    bool AreEqual(Vertex& v1, Vertex& v2)
    {
        for (unsigned int i{ 0 }; i < 8; i++)
            if (v1[i] != v2[i])
                return false;

        return true;
    }
    
    /// Get distance between 2 vectors
    float Distance(Vertex& v1, Vertex& v2)
    {
        float target{ 0.0f };

        for (unsigned int i{ 0 }; i < 4; i++)
            target += pow(v1[i] - v2[i], 2.0f);

        return sqrt(target);
    }
}
