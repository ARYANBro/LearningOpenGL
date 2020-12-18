@echo off

pushd %~dp0..\..\

if not exist ThirdParty\cmake\bin\cmake.exe (
    goto:CMakeNotFound
)

if not exist Binaries (
    goto:BinariesDirectoryNotFound
)

set target=all

if not "%~1" == "" (
    set target=%1
)

call ThirdParty\cmake\bin\cmake.exe --build Binaries --target %target% -j12
goto:Exit

:CMakeNotFound
    echo cmake.exe not found in ..\..\ThirdParty\cmake\bin\cmake.exe
    pause
    goto:Exit

:BinariesDirectoryNotFound
    echo Binaries directory does not exist
    pause
    goto:Exit

:Exit
    popd
    goto:eof

