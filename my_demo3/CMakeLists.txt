cmake_minimum_required(VERSION 3.1)
project (my_demo3)

set (CMAKE_CXX_STANDARD 14)

file(COPY ../shaders DESTINATION .)
file(COPY ../common_textures DESTINATION .)

# Source files
set (SOURCE_FILES
    my_demo3.cpp
    Shader.h
    )
# MESSAGE( STATUS "GLFW_LIB = " ${GLFW_LIB})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME}  MotokoGL Soil ${GL_LIBS}  ${OpenCV_LIBS}  ${CMAKE_THREAD_LIBS_INIT})
