////
//// Created by Igor Maschikevich on 10/03/2017.
////
////=================================================================================
//#include <iostream>
////=================================================================================
//#define GLEW_STATIC
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
////=================================================================================
//// Other Libs
//#include <SOIL.h>
////#include "Shader.h"
////=================================================================================
//const GLuint WindowWidth = 600;
//const GLuint WindowHeight = 400;
//const char* DefaultNameWindow = "SimpleWindow_8";
////=================================================================================
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
////=================================================================================
//const GLfloat vertices[] = {
//    // Positions         // Colors           // Texture Coords
//    //    0.5f, 0.5f, 0.0f,    1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
//    //    0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
//    //    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
//    //    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left

//    // Positions         // Colors           // Texture Coords
//    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
//    1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
//    -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
//    -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left
//};
////=================================================================================
//const GLuint indices[] = {  // Note that we start from 0!
//                            0, 1, 3 // First Triangle
//                            , 1, 2, 3  // Second Triangle
//                         };
////=================================================================================
//// Вершинный шейдер
//const GLchar *vertexShaderSource = "#version 330core\n"
//                                   "layout (location = 0 ) in vec3 position;\n"
//                                   "layout (location = 1) in vec3 color;\n"
//                                   "layout (location = 2) in vec2 texCoord;\n"

//                                   "out vec3 ourColor;\n"
//                                   "out vec2 TexCoord;\n"
//                                   "void main()\n"
//                                   "{\n"
//                                   "gl_Position = vec4(position, 1.0);\n"
//                                   "ourColor = color;\n"
//                                   "TexCoord = texCoord;\n"
//                                   "}\0";
////=================================================================================
//const GLchar * fragmentShaderSource = "#version 330 core\n"
//                                      "in vec3 ourColor;\n"
//                                      "in vec2 TexCoord;\n"
//                                      "out vec4 color;\n"
//                                      "uniform sampler2D ourTexture;\n"
//                                      "void main()\n"
//                                      "{\n"
//                                      "color = texture(ourTexture, TexCoord);\n"
//                                      "}\0";
////=================================================================================
//int main()
//{
//    // Init GLFW
//    glfwInit();
//    // Set all the required options for GLFW
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

//    // Create a GLFWwindow object that we can use for GLFW's functions
//    GLFWwindow* window = glfwCreateWindow(WindowWidth, WindowHeight, DefaultNameWindow, nullptr, nullptr);
//    glfwMakeContextCurrent(window);

//    // Set the required callback functions
//    glfwSetKeyCallback(window, key_callback);

//    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
//    glewExperimental = GL_TRUE;
//    // Initialize GLEW to setup the OpenGL Function pointers
//    glewInit();

//    // Define the viewport dimensions
//    glViewport(0, 0, WindowWidth, WindowHeight);
//    //=================================================================================
//    // Работа с  шейдерами
//    //=================================================================================
//    // Сборка вершинного шейдера
//    GLuint vertexShader;

//    vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource (vertexShader, 1, &vertexShaderSource, NULL);
//    glCompileShader(vertexShader);
//    //    проверка успешности сборки вершинного шейдера.
//    GLint success;
//    GLchar infoLog[512];
//    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//    if(!success)
//    {
//        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//    }
//    // сборка фрагментного шейдера
//    GLuint fragmentShader;
//    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//    glCompileShader(fragmentShader);

//    //    проверка успешности сборки фрагментного шейдера
//    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//    if (!success)
//    {
//        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
//    }
//    // Шейдерная программа
//    GLuint shaderProgram;
//    shaderProgram = glCreateProgram();
//    glAttachShader(shaderProgram, vertexShader);
//    glAttachShader(shaderProgram, fragmentShader);
//    glLinkProgram(shaderProgram);
//    //    проверка успешности связывания  с шейдерной програмой
//    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//    if(!success) {
//        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//        std::cout << "ERROR::SHADER::PROGRRAM::LINKING_FAILED\n" << infoLog << std::endl;
//    }
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);
//    //=================================================================================

//    //=================================================================================
//    GLuint VBO, VAO, EBO;
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//    glGenBuffers(1, &EBO);

//    glBindVertexArray(VAO);

//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

//    // Position attribute
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
//    glEnableVertexAttribArray(0);
//    // Color attribute
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//    glEnableVertexAttribArray(1);
//    // TexCoord attribute
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
//    glEnableVertexAttribArray(2);

//    glBindVertexArray(0); // Unbind VAO


//    // Load and create a texture
//    GLuint texture;
//    glGenTextures(1, &texture);
//    glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
//    // Set the texture wrapping parameters
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    // Set texture filtering parameters
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    // Load image, create texture and generate mipmaps
//    int width, height;
//    unsigned char* image = SOIL_load_image("common_textures/container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
//    //    unsigned char* image = SOIL_load_image("common_textures/container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//    glGenerateMipmap(GL_TEXTURE_2D);
//    SOIL_free_image_data(image);
//    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.


//    // Game loop
//    while (!glfwWindowShouldClose(window))
//    {
//        glfwPollEvents();
//        glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);


//        // Bind Texture
//        glBindTexture(GL_TEXTURE_2D, texture);

//        // Для использования созданной программы надо вызвать glUseProgram:
//        glUseProgram(shaderProgram);
//        // Draw container
//        glBindVertexArray(VAO);
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//        glBindVertexArray(0);

//        // Swap the screen buffers
//        glfwSwapBuffers(window);
//    }
//    // Properly de-allocate all resources once they've outlived their purpose
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
//    glDeleteBuffers(1, &EBO);
//    // Terminate GLFW, clearing any resources allocated by GLFW.
//    glfwTerminate();
//    return 0;
//}

//// Is called whenever a key is pressed/released via GLFW
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
//{
//    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, GL_TRUE);
//}
