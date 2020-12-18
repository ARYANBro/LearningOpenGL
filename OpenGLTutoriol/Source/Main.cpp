#include "OpenGLApplication.h"

#include <type_traits>
#include <memory>

int main()
{
    OpenGLApplication application(1280, 720);

    application.Run();
}
