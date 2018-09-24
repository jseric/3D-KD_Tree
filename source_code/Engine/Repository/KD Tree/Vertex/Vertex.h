#pragma once

#include "pch.h"

#include <DirectXMath.h>
#include <string>

namespace vxe
{
    class Vertex
    {
    public:
        DirectX::XMFLOAT4 position;
        DirectX::XMFLOAT4 color;

        Vertex(const float = 0.0f, const float = 0.0f,
               const float = 0.0f, const float = 1.0f,
               const float = 0.0f, const float = 0.0f,
               const float = 0.0f, const float = 0.0f);

        Vertex(DirectX::XMFLOAT4&,
               DirectX::XMFLOAT4&);;

        float& operator[](unsigned int);

        std::string ToString(void);

        void operator=(Vertex);
    };

    bool AreEqual(Vertex&, Vertex&);

    float Distance(Vertex&, Vertex&);
}

