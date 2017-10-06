//
// Created by Igor Maschikevich on 10/05/2017.
//
//==============================================================================================================
#include <iostream>
//#include <thread>
//#include <chrono>
#include <opencv2/opencv.hpp>
//==============================================================================================================
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
//==============================================================================================================
#include <SOIL.h>
#include "Shader.h"
#include "SyncBuf.h"
#include "MotokoGL.h"
//==============================================================================================================
const GLuint WindowWidth = 600;
const GLuint WindowHeight = 400;
const char* DefaultNameWindow = "my_demo1";
//==============================================================================================================
const char* setImage ="common_textures/container2.jpg";

//const char* setVertex ="shaders/textures.vert";
//const char* setFragment ="shaders/textures.frag";

const char* setVertex ="shaders/bg.vert";
const char* setFragment ="shaders/bg.frag";
//==============================================================================================================
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
//==============================================================================================================
const GLfloat vertices[] = {
    // Positions          // Colors            // Texture Coords
    1.0f,  1.0f, 0.0f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f, // Top Right
    1.0f, -1.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 0.0f, // Bottom Right
    -1.0f, -1.0f, 0.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, // Bottom Left
    -1.0f,  1.0f, 0.0f,    1.0f, 1.0f, 0.0f,    0.0f, 1.0f  // Top Left
};
//==============================================================================================================
const GLuint indices[] = {  // Note that we start from 0!
                            0, 1, 3, // First Triangle
                            1, 2, 3  // Second Triangle
                         };
//==============================================================================================================
int main(){
    using namespace MotokoGL;
    using namespace cv;
    using namespace std;
    cout << "OpenCV Version = " << CV_MAJOR_VERSION << "."<< CV_MINOR_VERSION << endl;

    //==============================================================================================

    //==============================================================================================
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WindowWidth, WindowHeight, DefaultNameWindow, nullptr, nullptr);
    const float aspectRatio = 1.0f * WindowWidth / WindowHeight;
    glfwMakeContextCurrent(window);

    // Set the required callback functions
    //    glfwSetKeyCallback(window, key_callback);

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    glewInit();
    // Define the viewport dimensions
    glViewport(0, 0, WindowWidth, WindowHeight);
    //==============================================================================================
    //==============================================================================================
    //==============================================================================================
    //    Shader
    Shader ourShader(setVertex, setFragment);
    //==============================================================================================

    //==============================================================================================
    //        Create  VBO, VAO, EBO;
    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //    //    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,  GL_DYNAMIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    // TexCoord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0); // Unbind VAO

    // Load and create a texture
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now
    //    have effect on this texture object
    // Set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
    //    (usually basic wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //     Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //==============================================================================================
    //    int width, height;
    //    unsigned char* image = SOIL_load_image(setImage, &width, &height, 0, SOIL_LOAD_RGB);
    //    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    //    glGenerateMipmap(GL_TEXTURE_2D);
    //    SOIL_free_image_data(image);
    //    glBindTexture(GL_TEXTURE_2D, 0);
    // Unbind texture when done, so we won't accidentily mess up our texture.
    //==============================================================================================
    //-------------------------------------------
    // Camera
    SimpleCamera camera;
    camera.aspect = aspectRatio;

    //-------------------------------------------
    // GLFW game loop
    //-------------------------------------------

    VideoCapture cap(0);
    Mat frame;
    cap.read(frame);
    Tex texBG = Tex::fromMat(frame);
    texBG.setToNearest();
    //==============================================================================================
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Get frame
        cap.read(frame);
        cap.retrieve(frame);
        //        texBG.updateImage(frame);

        // Render Background

        // Clear screen
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // RGBA
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // ====Draw background
        //        glDisable(GL_DEPTH_TEST);
        progBG.use();
        //        texBG.bind(0);
        //        glUniform1i(progBG.loc("uTex"), 0);
        //        vaoBG.draw();
        //        glEnable(GL_DEPTH_TEST);

        window.swapBuffers();
        //        //        glfwPollEvents();
        //        glDisable(GL_DEPTH_TEST);

        //        glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
        //        glClear(GL_COLOR_BUFFER_BIT);
        //        // Bind Texture
        //        glBindTexture(GL_TEXTURE_2D, texture);
        //        // Для использования созданной программы надо вызвать glUseProgram:
        //        ourShader.Use();
        //        // Draw container
        //        glBindVertexArray(VAO);
        //        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //        glBindVertexArray(0);
        //        // Swap the screen buffers
        //        glfwSwapBuffers(window);

        // Draw the window (Swap buffers)
        //        window.swapBuffers();
    }
    //==============================================================================================
    // DElet all res.
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    //==============================================================================================
    return 0;
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}
//==================================================================================================================
// By Oleksiy Grechnyev
// DEMO: openGl object drawn on the camera frame, multithreaded version


//// System headers
//#include <iostream>
//#include <cmath>
//#include <ctime>
//#include <thread>
//#include <chrono>

//#include <opencv2/opencv.hpp>

//#include "MotokoGL.h"
//#include "SyncBuf.h"

////=============================================================
//inline static GLfloat funCos(GLfloat x) {
//    return 0.5f * (cosf(x) + 1);
//}


////=============================================================
//int main() {
//    using namespace MotokoGL;
//    using namespace glm;
//    using namespace cv;

//    using namespace std;
//    using namespace std::chrono;


//    SyncBuf<Mat> buf1; // Captured image before processing
//    // The counters, for FPS, count camera frames and GL renders
//    int countCam = 0, countGL = 0;
//    using DSeconds = duration<double>;  // Double seconds for duration casts
//    bool stopFlag = false;
//    //-------------------------------------------
//    // Camera capture thread
//    //-------------------------------------------

//    thread captureThread([&buf1, &countCam, &stopFlag]() -> void {
//        VideoCapture cap(0);
//        while (!stopFlag) {
//            int ind;

//            // Capture a frame
//            Mat &frame = buf1.startWriting(ind);  // Request bufffer slot
//            cap.read(frame);
//            buf1.endWriting(ind);     // End buffer slot
//            ++countCam;
//        }
//    });

//    //-------------------------------------------
//    // FPS measurement thread
//    //-------------------------------------------
//    thread fpsThread([&countCam, &countGL, &stopFlag]() -> void {

//        auto tp0 = high_resolution_clock::now();  // Start time
//        while (!stopFlag) {
//            // Time in seconds, C++ version
//            auto tp = high_resolution_clock::now();
//            double t = duration_cast<DSeconds>(tp - tp0).count();
//            // Count FPS about once / 10 sec
//            if (t > 10.0) {
//                cout << "FPS CAM = " << countCam / t << endl;
//                cout << "FPS GL = " << countGL / t << endl;
//                countCam = countGL = 0; // Reset counts
//                tp0 = tp;   // Reset time
//            }
//        }
//    });

//    //-------------------------------------------
//    // OpenGL render thread
//    //-------------------------------------------
//    thread renderThread([&buf1, &countGL, &stopFlag]() -> void {

//        // GLFW window
//        Window window(800, 600, "Goblin OpenGL Demo 3");
//        const float aspectRatio = 1.0f * window.getWidth() / window.getHeight();

//        auto tp0 = high_resolution_clock::now();  // Start time
//        //    glEnable(GL_DEPTH_TEST); // Enable depth test, important
//        // ============Background
//        ShaderProg progBG = ShaderProg::fromFiles("shaders/bg.vert", "shaders/bg.frag");
//        // Square, with EBO
//        GLfloat verticesBG[] = {
//            1.0f, 1.0f, 0.0f, 1.0, 1.0,  // UR
//            1.0f, -1.0f, 0.0f, 1.0, 0.0,  // LR
//            -1.0f, -1.0f, 0.0f, 0.0, 0.0,  // LL
//            -1.0f, 1.0f, 0.0f, 0.0, 1.0   // UL
//        };
//        GLuint indicesBG[] = {
//            0, 1, 3,
//            1, 2, 3
//        };
//        // VAO for square (EBO)
//        Vao vaoBG({3, 0, 2}, verticesBG, sizeof(verticesBG), indicesBG, sizeof(indicesBG));

//        //================== Cube
//        ShaderProg objProg = ShaderProg::fromFiles("shaders/obj.vert", "shaders/obj.frag");
//        // A cube XYZ_NORMAL_TEX
//        GLfloat vert[] = {
//            // Positions          // Normals           // Texture Coords
//            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
//            0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
//            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
//            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
//            -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
//            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

//            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
//            0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
//            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
//            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
//            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
//            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

//            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
//            -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
//            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
//            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
//            -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
//            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

//            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
//            0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
//            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
//            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
//            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
//            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

//            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
//            0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
//            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
//            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
//            -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
//            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

//            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
//            0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
//            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
//            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
//            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
//            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
//        };
//        // VAO
//        // XYZ_NORM_TEX
//        Vao objVao({3, 3, 2}, vert, sizeof(vert));
//        //-------------------------------------------
//        // Texture
//        Tex texO = Tex::fromFile("common_textures/container2.jpg");

//        //-------------------------------------------
//        // Camera (OpenGL camera, not the web-camera)
//        SimpleCamera camera;
//        camera.aspect = aspectRatio;

//        // Get the first frame to set up texture
//        Mat firstFrame;
//        for (;;) {
//            int ind;
//            firstFrame = buf1.startReading(ind);
//            // Wait until we get a frame
//            if (ind != -1)
//                break;
//            else
//                this_thread::sleep_for(chrono::milliseconds(10)); // No data available for now, we wait
//        }
//        Tex texBG = Tex::fromMat(firstFrame);
//        texBG.setToNearest();

//        // ============== GLFW game loop
//        while (!stopFlag) {
//            glfwPollEvents();
//            if (window.shouldClose()) {
//                stopFlag = true;
//                break;
//            }
//            // Time in seconds, C++ version
//            auto tp = high_resolution_clock::now();
//            double t = duration_cast<DSeconds>(tp - tp0).count();

//            // =========Render Background
//            // Check for next frame
//            int ind;
//            const Mat &frame = buf1.startReading(ind); // Try to read
//            if (-1 != ind) {
//                texBG.updateImage(frame);  // Update texture if a frame is available, non-blocking
//                buf1.endReading(ind);
//            }

//            // Clear screen
//            ++countGL;
//            glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // RGBA
//            int errorCode = glGetError();
//            if (errorCode > 0) {
//                std::cout << "MARIA_ERROR :" << errorCode << std::endl;
//            }

//            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//            // ====Draw background
//            glDisable(GL_DEPTH_TEST);
//            progBG.use();
//            texBG.bind(0);
//            glUniform1i(progBG.loc("uTex"), 0);
//            vaoBG.draw();
//            glEnable(GL_DEPTH_TEST);

//            // =============== Render the model
//            // Set up the camera pos if needed
//            camera.pos = vec3(2.0f, 2.0f, 7.0f);
//            // Camera matrix
//            mat4 cam = camera.matrix();
//            // Model matrix
//            mat4 model;

//            //===== Render the cube
//            objProg.use(); // Use program

//            texO.bind(0);  // Texture
//            glUniform1i(objProg.loc("uTex"), 0);

//            // Set model matrix
//            model = mat4();
//            model = rotate(model, ((float) t) * sqrtf(0.5f), vec3(1.0f, 0.5f, 0.0f)); // Rotate
//            objProg.setMatCM(cam, model);
//            // Set material
//            objVao.draw(); // Draw the cube

//            // ====Draw the window (Swap buffers)
//            window.swapBuffers();
//        }

//        glfwTerminate(); // Stop openGL
//    });

//    cout << "Joining threads ..." << endl;

//    // Join all threads: not at present
//    captureThread.join();
//    renderThread.join();
//    fpsThread.join();

//    return 0;
//}
