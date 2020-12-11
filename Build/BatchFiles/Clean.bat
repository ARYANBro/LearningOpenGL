@echo off

pushd %~dp0..\..\

rem First make sure we have mingw32-make.exe and Binaries directory

where /Q mingw32-make.exe

if ERRORLEVEL 1 (
	goto:MinGW32-MakeNotFound
)

if not exist Binaries (
	goto:BinariesDirectoryNotExist
)

pushd Binaries

if "%~1" == "" (
	echo Cleaning Build

	call mingw32-make.exe clean

	echo Sucessfully cleaned Build
) else (
	if not exist "%~1" (
		goto:UserDefinedDirectoryNotFound
	)

	pushd %1
	echo Cleaning %1

	mingw32-make.exe clean

	echo Sucessfully cleaned %1
	popd
)

popd

goto:Exit

:MinGW32-MakeNotFound
	echo mingw32-make.exe not found in the system path
	pause
	goto:Exit

:BinariesDirectoryNotExist
	echo Binaries directory does not exist
	pause
	goto:Exit

:UserDefinedDirectoryNotFound
	echo Directory %1 doesn't exist
	pause
	goto:Exit

:Exit
	popd
	goto:eof
