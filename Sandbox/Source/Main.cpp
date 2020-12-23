#include "Sandbox.h"

#include <type_traits>
#include <memory>

int main()
{
    Sandbox sandbox(1600, 900);

    sandbox.Run();
}
