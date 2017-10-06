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
const char* DefaultNameWindow = "SimpleWindow_3";
//================================================================================
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
//================================================================================
// Координати трикутника
GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f
};
//================================================================================
// Вершинный шейдер
const GLchar *vertexShaderSource = "#version 330core\n"
                                   "layout (location = 0 ) in vec3 position;\n"
                                   "void main()\n"
                                   "{\n"
                                   "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
                                   "}\0";
//================================================================================
const GLchar * fragmentShaderSource = "#version 330 core\n"
                                      "out vec4 color;\n"
                                      "void main()\n"
                                      "{\n"
                                      "color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                      "}\0";
//================================================================================
//================================================================================
//================================================================================

int main()
{
    //*******************************************************************************************************
    // Стандартне створення вікна
    //*******************************************************************************************************

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
    //================================================================================
    // Вкажіть необхідні функції зворотного виклику
    glfwSetKeyCallback(window, key_callback);
    //================================================================================
    // Ініциалізація GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK){
        std::cout << "Faild to initialize GLEW" << std::endl;
        return -1;
    }
    //================================================================================
    //размер отрисовываемого окна
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    //================================================================================
    //*******************************************************************************************************
    // Работа с  шейдерами
    //================================================================================
    // Сборка вершинного шейдера
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource (vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    //    проверка успешности сборки вершинного шейдера.
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // сборка фрагментного шейдера
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    //    проверка успешности сборки фрагментного шейдера
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // Шейдерная программа
    GLuint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    //    проверка успешности связывания  с шейдерной програмой
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    //================================================================================
    // Код инициализации (выполняется единожды (если, конечно, объект не будет часто изменяться)) :: ..
    GLuint VBO, VAO;
    // 1. Привязываем VAO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);
    // 2. Копируем наш массив вершин в буфер для OpenGL
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. Устанавливаем указатели на вершинные атрибуты
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //4. Отвязываем VAO
    glBindVertexArray(0);
    //================================================================================
    // Игровой цикл
    while (!glfwWindowShouldClose(window))
    {
        //Для использования созданной программы надо вызвать glUseProgram:

        glfwPollEvents();
        glClearColor(0.2f, 0.6f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //Для использования созданной программы надо вызвать glUseProgram:
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        glfwSwapBuffers(window);

    }
    //================================================================================
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;

}
//================================================================================
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_Q && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}
//================================================================================
