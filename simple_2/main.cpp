//
// Created by Igor Maschikevich on 9/28/2017.
//
//================================================================================
#include <iostream>
#include <string>
//================================================================================
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
//================================================================================
const GLuint WindowWidth = 600;
const GLuint WindowHeight = 400;
const char* DefaultNameWindow = "SimpleWindow_2";
//================================================================================
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
//================================================================================
int main(){
    //    Ініциалізація GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // вівмкнення зміни розміру вікна
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    // потрібно для Mac OS X
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //объект окна
    GLFWwindow* window = glfwCreateWindow(WindowWidth, WindowHeight, DefaultNameWindow, nullptr, nullptr);
    if (window == nullptr){
        std::cout <<"Failed to create GLEW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);

    // Вкажіть необхідні функції зворотного виклику
    glfwSetKeyCallback(window, key_callback);
    // Ініциалізація GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK){
        std::cout << "Faild to initialize GLEW" << std::endl;
        return -1;
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    // Игровой цикл
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.2f, 0.6f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
//================================================================================
// Закриття вікна при натискані кнопки q
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
    std::cout << key << std::endl;
    if(key == GLFW_KEY_Q && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if(key == GLFW_KEY_UP && action == GLFW_PRESS)
        glfwSetWindowSize(window, WindowWidth, 500);
    if(key == GLFW_KEY_DOWN && action == GLFW_PRESS)
        glfwSetWindowSize(window, WindowWidth, WindowHeight);
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowTitle(window, "ZAMEHA HA-HA-HA !!! Enter: q");
}
//================================================================================
