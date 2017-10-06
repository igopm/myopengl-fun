//
// Created by Igor Maschikevich on 9/28/2017.
//
//================================================================================
#include <iostream>
//================================================================================
//#include "window.h"
//================================================================================
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
//================================================================================
int WindowWidth = 800;
int WindowHeight = 600;

//int width, int height
//================================================================================
int main(){
    // Ініциалізація GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // вівмкнення зміни розміру вікна
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    // потрібно для Mac OS X
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //объект окна
    GLFWwindow* window = glfwCreateWindow(WindowWidth, WindowHeight, "SimpleWindow_1", nullptr, nullptr);
    if (window == nullptr){
        std::cout <<"Failed to create GLEW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    // Ініциалізація GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK){
        std::cout << "Faild to initialize GLEW" << std::endl;
        return -1;
    }
    glfwGetFramebufferSize(window, &WindowWidth, &WindowHeight);
    glViewport(0, 0, WindowWidth, WindowHeight);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}
