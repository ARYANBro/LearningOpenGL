project(Sandbox)

file(GLOB_RECURSE SourceFiles
    "Source/*.cpp"
    "Source/*.h"
    "ThirdParty/stb_image/source/*.cpp"
)

add_compile_definitions(
    $<$<CONFIG:Debug>:ENABLE_DEBUG_MACROS>
    GLFW_INCLUDE_NONE
)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    add_compile_options(
        -Wsign-conversion
        -pedantic-errors
        -Wextra
        -Wall
    )
endif()

add_executable(${PROJECT_NAME} ${SourceFiles})

target_link_libraries(${PROJECT_NAME}
    Opengl32
    glfw
    Glad
    StbImage
    glm
    ImGui
)

target_include_directories(${PROJECT_NAME}
    PUBLIC Include
)
