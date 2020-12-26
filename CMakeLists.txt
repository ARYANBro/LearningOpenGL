cmake_minimum_required(VERSION 3.10)

project(OpenGLTutoriol)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)

set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 20)

set(OutDirectory ${CMAKE_BUILD_TYPE})

# Project targets
add_subdirectory(Sandbox ${OutDirectory}/Sandbox)

# Thirdparty targets
add_subdirectory(Sandbox/ThirdParty/GLFW ${OutDirectory}/ThirdParty/GLFW)
add_subdirectory(Sandbox/ThirdParty/Glad ${OutDirectory}/ThirdParty/Glad)
add_subdirectory(Sandbox/ThirdParty/stb_image ${OutDirectory}/ThirdParty/stb_image)
add_subdirectory(Sandbox/ThirdParty/glm ${OutDirectory}/ThirdParty/glm)
add_subdirectory(Sandbox/ThirdParty/ImGui ${OutDirectory}/ThirdParty/ImGui)
