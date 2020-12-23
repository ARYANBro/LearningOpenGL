project(StbImage)

add_library(StbImage INTERFACE)

target_include_directories(${PROJECT_NAME}
	SYSTEM INTERFACE include
)
