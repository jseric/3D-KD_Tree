#pragma once

#include "..\..\Engine\Core\Content\RendererBase3D.h"

/*
 * Vanity DirectX Engine namespace
 */
namespace vxe
{
    class Renderer3D : public RendererBase3D
    {
    public:
        Renderer3D(void);

        void CreateDeviceDependentResources(void) override;

        void CreateWindowSizeDependentResources(void) override;

        void ReleaseDeviceDependentResources(void) override;

        void Render(void) override;
    };
}
