#include "pch.h"

#include "Vertex.h"

#include <cmath>

namespace vxe
{
    bool AreEqual(DirectX::VertexPosition& v1, DirectX::VertexPosition& v2)
    {
        for (unsigned int i{ 0 }; i < 3; i++)
            if (v1[i] != v2[i])
                return false;

        return true;
    }
    
    float Distance(DirectX::VertexPosition& v1, DirectX::VertexPosition& v2)
    {
        float target{ 0.0f };

        for (unsigned int i{ 0 }; i < 4; i++)
            target += pow(v1[i] - v2[i], 2.0f);

        return sqrt(target);
    }
}
