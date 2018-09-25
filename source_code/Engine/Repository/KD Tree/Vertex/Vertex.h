#pragma once

#include "pch.h"

#include "..\..\..\Third Party\DirectX Tool Kit\VertexTypes.h"

#include <DirectXMath.h>
#include <string>

namespace vxe
{
    bool AreEqual(DirectX::VertexPosition&, DirectX::VertexPosition&);

    float Distance(DirectX::VertexPosition&, DirectX::VertexPosition&);
}

