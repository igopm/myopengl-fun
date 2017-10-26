cmake_minimum_required(VERSION 3.1)
project (myopengl-fun)

set (CMAKE_CXX_STANDARD 14)

# OpenGL, GLEW, GLFW :
FIND_LIBRARY(GLFW_LIB NAMES glfw glfw3)
FIND_LIBRARY(GLEW_LIB NAMES glew GLEW glew32)
find_package(OpenGL REQUIRED)
set(GL_LIBS  ${GLEW_LIB} ${GLFW_LIB} ${OPENGL_gl_LIBRARY})

# Set include dirs
include_directories(
    MotokoGL
    Soil
    )

# OpenCV
if(WIN32)
    set(OpenCV_DIR c:/opencv)
else()
    set(OpenCV_DIR  ~/opencv3/share/OpenCV)
endif()

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# Threads
#find_package(Threads)

# Build SOIL library
add_subdirectory(Soil)

# Build MotokoGL library
add_subdirectory(MotokoGL)

#add_subdirectory(simple_1)
#add_subdirectory(simple_2)
#add_subdirectory(simple_3)
#add_subdirectory(simple_4)
#add_subdirectory(simple_5)
#add_subdirectory(simple_6)
#add_subdirectory(simple_7)
add_subdirectory(simple_8)
#add_subdirectory(my_opencv)
add_subdirectory(my_demo3)
