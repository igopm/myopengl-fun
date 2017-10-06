cmake_minimum_required(VERSION 3.0)
project (MotokoGL)

set (CMAKE_CXX_STANDARD 14)

# Source files
set (SOURCE_FILES
      ./glheader.h
      ./fatal.h
      ./Window.cpp ./Window.h
      ./ShaderProg.cpp ./ShaderProg.h
      ./IVao.h
      ./Vao.h ./Vao.cpp
      ./Tex.h ./Tex.cpp
      ./SimpleCamera.h
      ./Material.h
      ./MaterialT.h
      ./MotokoGL.h
      ./Light.h
        )

add_library(MotokoGL ${SOURCE_FILES})
