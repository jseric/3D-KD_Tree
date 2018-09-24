#include "pch.h"
#include "Renderer3D.h"

#include <vector>
#include <string>

namespace vxe
{
    /*
     * Default constructor
     */
    Renderer3D::Renderer3D(void) : RendererBase3D()
    {
        DebugPrint(std::string("vxe::Renderer::Renderer3D() called..."));
    }

    /*
     * Create device dependent resources:
     * the device and context objects
     */
    void Renderer3D::CreateDeviceDependentResources(void)
    {
        DebugPrint(std::string("\t Renderer3D::CreateDeviceDependentResources() called... \n"));

        auto device = m_deviceResources->GetD3DDevice();

        std::vector<concurrency::task<void>> tasks;

        concurrency::when_all(tasks.begin(), tasks.end())
            .then([this]()
        {
            m_loadingComplete = true;
            DebugPrint(std::string("\t -- A lambda: Loading is complete! \n"));
        });
    }

    /*
     * Create window-size dependent resources:
     * resources that depend on the size of the
     * rendering window, like:
     *
     * - A SwapChain object
     * - A RenderTargetView object
     * - DepthStencilBuffer and DepthStencilView objects
     * - A VIEWPORT object
     * - A TargetBitMap object
     */
    void Renderer3D::CreateWindowSizeDependentResources(void)
    {
        DebugPrint(std::string("\t Renderer3D::CreateWindowSizeDependentResources() called... \n"));

        auto device = m_deviceResources->GetD3DDevice();
        auto context = m_deviceResources->GetD3DDeviceContext();

        Windows::Foundation::Size outputSize = m_deviceResources->GetOutputSize();

        DebugPrint(std::string("\t\t Width: ") +
                   std::to_string(outputSize.Width) +
                   std::string("\n"));

        DebugPrint(std::string("\t\t Height: ") +
                   std::to_string(outputSize.Height) +
                   std::string("\n"));
    }

    /*
     * (Release) free device dependent resources,
     * created in Renderer3D::CreateDeviceDependentResources()
     */
    void Renderer3D::ReleaseDeviceDependentResources(void)
    {
        DebugPrint(std::string("Renderer3D::ReleaseDeviceDependentResources() called..."));

        m_loadingComplete = false;
    }

    /*
     * Function that simulates rendering
     */
    void Renderer3D::Render(void)
    {
        DebugPrint(std::string("\t Renderer3D::Render() called... \n"));

        if (!m_loadingComplete)
            return;

        auto context = m_deviceResources->GetD3DDeviceContext();

        ID3D11RenderTargetView *const targets[1] = {
            m_deviceResources->GetBackBufferRenderTargetView() };

        context->OMSetRenderTargets(1, targets,
            m_deviceResources->GetDepthStencilView());

        m_deviceResources->SetRasterizerState();
    }
}
