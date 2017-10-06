cmake_minimum_required(VERSION 3.1)
project (simple_6)

set (CMAKE_CXX_STANDARD 14)

FIND_LIBRARY(GLFW_LIB NAMES glfw glfw3)
FIND_LIBRARY(GLEW_LIB NAMES glew GLEW glew32)
FIND_LIBRARY(GL_LIB NAMES gl GL opengl opengl32)
# Source files
set (SOURCE_FILES
    main.cpp
    )


# MESSAGE( STATUS "GLFW_LIB = " ${GLFW_LIB})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${GLFW_LIB} ${GLEW_LIB} ${GL_LIB})


