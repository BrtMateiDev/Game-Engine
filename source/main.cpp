#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main() {
    if (!glfwInit()) return -1;

    //Telling OpenGL what version to expect
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //The window acts as an object stored in a pointer
    GLFWwindow *window = glfwCreateWindow(1280, 720, "GameDevelopmentProject", nullptr, nullptr);

    if (window == nullptr) {
        std::cout<<"Error creating window"<<'\n';
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); //Telling OpenGL what window to target

    if (glewInit() != GLEW_OK) {
        std::cout<<"Error initializing GLEW"<<'\n';
        glfwTerminate();
        return -1;
    }

    while (!glfwWindowShouldClose(window)) {
        glClearColor(1, 0, 0, 1); //each number is for the color channels
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window); //swapping the back buffer to the front buffer

        glfwPollEvents(); //Events like the close button
    }

    glfwTerminate();

    return 0;
}