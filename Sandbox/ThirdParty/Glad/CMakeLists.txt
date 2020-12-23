project(Glad)

set(SourceFiles 
	"src/glad.c"
)

add_library(Glad ${SourceFiles})

target_include_directories(${PROJECT_NAME}
	PUBLIC "include"
)
