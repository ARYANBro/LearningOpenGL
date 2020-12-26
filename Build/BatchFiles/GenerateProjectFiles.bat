@echo off

setlocal EnableDelayedExpansion

pushd %~dp0..\..\

if not exist ThirdParty\cmake\bin\cmake.exe (
    goto:CMakeNotFound
)

rem %1 is the build configuration
rem %2 is the generator of the build

set buildConfigurations=Debug Release RelWithDebInfo MinSizeRel

rem Options
set generator="MinGW Makefiles"
set CMAKE_BUILD_TYPE=Debug
set GLFW_BUILD_EXAMPLES=OFF
set GLFW_BUILD_TESTS=OFF
set GLFW_BUILD_DOCS=OFF

if not "%~1" == "" (
    for %%i in (%buildConfigurations%) do (
        
        rem Check if the user doesn't provide invalid build configuration
        if "%%i" == "%~1" (
            set CMAKE_BUILD_TYPE=%1
            goto:Generate
        )
    )

    goto:InvalidConfiguration
)

:Generate

set options=-DCMAKE_BUILD_TYPE=%CMAKE_BUILD_TYPE%
set options=%options% -DGLFW_BUILD_EXAMPLES=%GLFW_BUILD_EXAMPLES%
set options=%options% -DGLFW_BUILD_TESTS=%GLFW_BUILD_TESTS%
set options=%options% -DGLFW_BUILD_DOCS=%GLFW_BUILD_DOCS%

if not "%~2" == "" (
    set generator=%2
)
    echo Generating %CMAKE_BUILD_TYPE% configuration

    call ThirdParty\cmake\bin\cmake.exe %options% -G%generator% -S %~dp0..\..\ -B Binaries
    goto:Exit

:InvalidConfiguration
    echo Specified configuration is invalid
    pause
    goto:Exit

:CMakeNotFound
    echo cmake.exe not found in ..\..\ThirdParty\cmake\bin\cmake.exe
    pause
    goto:Exit

:Exit
    popd
    goto:eof
