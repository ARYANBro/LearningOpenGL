#include "OpenGLApplication.h"

#include <memory>

int main()
{
    std::unique_ptr<Application> application = std::make_unique<OpenGLApplication>();

    application->Run();
}
