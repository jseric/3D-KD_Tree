#include "pch.h"
#include "Renderer3D.h"

#include "..\..\Engine\Models\Basic Shapes\Pyramids.h"
#include "..\..\Engine\Models\Basic Shapes\Cubes.h"
#include "..\..\Engine\Models\Basic Shapes\Triangles.h"

#include "..\..\Engine\Models\Explicit Surface.h"

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

        // Create vertex shader and pixel shader object
        _vertexShader = std::make_shared<VertexShader<DirectX::VertexPositionColor>>();
        _pixelShader = std::make_shared<PixelShader>();

        tasks.push_back(_vertexShader->CreateAsync(device,
            std::wstring(L"Vertex Shader.cso")));

        tasks.push_back(_pixelShader->CreateAsync(device,
            std::wstring(L"Pixel Shader.cso")));

        // Create a model of a pyramid/cube/triangle/function y=f(x,z)
        _models.push_back(std::make_shared<Pyramid<DirectX::VertexPositionColor, unsigned short>>());
        //_models.push_back(std::make_shared<Cube<DirectX::VertexPositionColor, unsigned short>>());
        //_models.push_back(std::make_shared<Triangle<DirectX::VertexPositionColor, unsigned short>>());
        /*
        _models.push_back = std::make_shared
            <ExplicitSurface<DirectX::VertexPositionColor, unsigned short>>
            (20.0f, 20.0f, 100, 100, [](float x, float z)
            {
            return 10 * expf(-(powf(x, 2.0f)) / 16.0f) *
                expf(-(powf(z, 2.0f)) / 16.0f);
            });
        */
        
        // Push vertex shader object, pixel shader object and model
        // to list of async tasks
        for (auto& _model : _models)
            tasks.push_back(_model->CreateAsync(device));

        concurrency::when_all(tasks.begin(), tasks.end())
            .then([this]()
        {
            m_loadingComplete = true;
            DebugPrint(std::string("\t -- A lambda: Loading is complete! \n"));
        });

        // Create a world transform object
        _world = std::make_shared<WorldTransforms>(device);
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

        // Create the view transform and define it
        _view = std::make_shared<ViewTransform>(device);

        // Position(s) of the camera
        //static const DirectX::XMVECTORF32 eye{ 0.0f, 0.0f, 3.0f, 0.0f };
        static const DirectX::XMVECTORF32 eye{ 0.0f, 10.0f, 15.0f, 0.0f };

        static const DirectX::XMVECTORF32 at{ 0.0f, 0.0f, 0.0f, 0.0f };
        static const DirectX::XMVECTORF32 up{ 0.0f, 1.0f, 0.0f, 0.0f };

        _view->SetView(eye, at, up);
        _view->Update(context);

        // Create the projection transform
        float r{ outputSize.Width / outputSize.Height };
        float fov{ 70.0f * DirectX::XM_PI / 180.0f };
        float n{ 0.01f };
        float f{ 1000.0f };

        if (r < 1.0f)
            fov *= 2.0f;

        DirectX::XMFLOAT4X4 orientation{ m_deviceResources->GetOrientationTransform3D() };
        DirectX::XMMATRIX orientationMatrix{ DirectX::XMLoadFloat4x4(&orientation) };

        _projection = std::make_shared<ProjectionTransform>(device);
        _projection->SetProjection(orientationMatrix, fov, r, n, f);

        _projection->Update(context);
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

        // Bind the vertex shader and pixel
        // shader to the pipeline
        _vertexShader->Bind(context);
        _pixelShader->Bind(context);

        // Bind the world, view and
        // projection transform to the
        // pipeline
        SetCamera();

        // Execute the pipeline
        for (auto& _model : _models)
            Draw(_model, _world);

        m_deviceResources->SetRasterizerState();
    }

    /*
     * Rotate the world matrix
     */
    void Renderer3D::Rotate(float radians)
    {
        _world->RotateY(radians);
    }

    /*
     * Bind view and projection matrices
     * to the pipeline
     */
    void Renderer3D::SetCamera(void)
    {
        auto context = m_deviceResources->GetD3DDeviceContext();

        _view->GetConstantBuffer()->Bind(
            context,
            ProgrammableStage::VertexShaderStage,
            1);

        _projection->GetConstantBuffer()->Bind(
            context,
            ProgrammableStage::VertexShaderStage,
            2);
    }

    /*
     * Execute the pipeline for _model
     */
    template <typename T, typename U>
    void Renderer3D::Draw(std::shared_ptr<MeshBase<T, U>>& mesh,
        std::shared_ptr<WorldTransforms>& world,
        bool indexed)
    {
        auto context = m_deviceResources->GetD3DDeviceContext();

        world->Update(context);
        world->GetConstantBuffer()->Bind(context);

        mesh->BindVertexBuffer(context);
        mesh->BindIndexBuffer(context);

        if (indexed)
            mesh->DrawIndexed(context);
        else
            mesh->Draw(context);
    }

    /*
     * Reset all resources
     */
    void Renderer3D::Reset(void)
    {
        _vertexShader->Reset();
        _pixelShader->Reset();

        for (auto& _model : _models)
            _model->Reset();

        _world->Reset();
        _view->Reset();
        _projection->Reset();
    }
}
