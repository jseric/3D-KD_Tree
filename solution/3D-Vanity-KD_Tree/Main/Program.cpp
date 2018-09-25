#include "pch.h"

#include "Renderer3D.h"

#include <string>

#define EXIT_SUCCESS 0

using namespace Platform;
using namespace Windows::ApplicationModel::Core;

using namespace vxe;
using namespace std;

[MTAThread]
auto main(Array<String ^>^)->int
{
    vxe::DebugPrint(std::string("main() started... \n"));

    shared_ptr<RendererBase3D> renderer3D = make_shared<Renderer3D>();

    auto factory = ref new ApplicationFactory(renderer3D);
    CoreApplication::Run(factory);

    return EXIT_SUCCESS;
}